/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Managed signal-slot object, with limited functionality

#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <list>
#include <memory>

namespace coffee {
namespace engine {

// Connection id type
using connection_t = uint64_t;

// Using partial template specialization to define the function
// signature as a template arg
template <class>
class Signal;

// Managed signal-slot system
// Does not currently support collectors, but silently swallows return types
// Not thread safe
template <class R, class... Args>
class Signal<R(Args...)> {
    using slot_t = std::function<R(Args...)>;
    using tracker_t = std::weak_ptr<void>;

    // callback and associated data
    struct Slot {
        std::shared_ptr<slot_t>
            callback;  // FIXME: do we even need to use a shared ptr?  The
                       // signal is not managing lifetime, and few (none?)
                       // managed callbacks should be passed in
        tracker_t tracker;
        bool tracked = false;
    };

   public:
    Signal() = default;
    explicit Signal(const slot_t& callback) { connect(callback); }
    // Create a slot by binding a member function to the pointer of an instance
    template <class Instance, class Class>
    Signal(Instance* instance, R (Class::*method)(Args...)) {
        connect(std::bind(method, instance));
    }

    ~Signal() = default;
    explicit Signal(const Signal& other) = delete;
    explicit Signal(Signal&& other) = delete;
    Signal& operator=(const Signal& other) = delete;
    Signal& operator=(Signal&& other) = delete;

    // Connect a listener (unmanaged)
    connection_t connect(const slot_t& callback) {
        return connectImpl(callback, tracker_t(), false);
    }

    // Create a slot by binding a member function to the pointer of an instance
    template <class Instance, class Class, class... Params>
    connection_t connect(Instance* instance, R (Class::*method)(Args...),
                         Params... params) {
        // Binding class pointer as the (implied) first argument of its member
        // function
        return connectImpl(std::bind(method, instance, params...), tracker_t(),
                           false);
    }

    // Create a slot by binding a member function to the pointer of an instance
    template <class Instance, class Class, class... Params, class TrackedT>
    connection_t connectManaged(const std::shared_ptr<TrackedT>& trackingObject,
                                Instance* instance, R (Class::*method)(Args...),
                                Params... params) {
        // Binding class pointer as the (implied) first argument of its member
        // function
        connection_t id = connectImpl(std::bind(method, instance, params...),
                                      tracker_t(trackingObject), true);

        return id;
    }

    // Trigger the signal (interrupting)
    void operator()(Args... args) {
        cullTrackedItems();  // Ensure that all tracked connections are live

        for (auto& s : _connections) {
            if (s.callback.get()) {  // FIXME: is this check necessary?  should
                                     // it just be check on connection?
                // invoke the callback
                (*s.callback)(args...);
            }
        }
    }

    // Disconnect all listeners
    void disconnectAll() { _connections.clear(); }

    // Disconnect listener by id
    bool disconnect(connection_t id) {
        size_t nRemoved =
            _connections.remove_if([id](const auto& elem) -> bool {
                // Simultaneously performing a cull of expired tracked items
                bool expiredTracker = elem.tracker.expired() && elem.tracked;
                // Check id
                return id == connection_t(elem.callback.get()) ||
                       expiredTracker;
            });

        return nRemoved > 0;
    }

    // Number of listeners currently connected
    size_t countActiveConnection() {
        cullTrackedItems();
        return _connections.size();
    }

   private:
    std::list<Slot> _connections;

    // Implementation of adding a new connection
    connection_t connectImpl(const slot_t& callback,
                             const tracker_t& trackingObject, bool tracked) {
        auto& ref = _connections.emplace_back(
            std::make_shared<slot_t>(callback), trackingObject, tracked);

        cullTrackedItems();

        return connection_t(ref.callback.get());
    }

    // Check lifetime of tracked connections, and update if any connections have
    // gone out of scope
    void cullTrackedItems() {
        _connections.remove_if([](const auto& elem) -> bool {
            bool expiredTracker = elem.tracker.expired() && elem.tracked;
            return expiredTracker;
        });
    }
};

}  // namespace engine
}  // namespace coffee