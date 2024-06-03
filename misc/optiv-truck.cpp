// https://leetcode.com/discuss/interview-question/3816133/Optiver-or-OA-or-Truck-Positions

#include <cstdint>
#include <functional>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>

struct TruckPosition
{
  float x{ 0 };
  float y{ 0 };
};

struct TruckPositionDelta
{
  std::uint64_t truck_id;
  float x;
  float y;
};

class Server
{
public:
  using Callback = std::function<void(const TruckPositionDelta&)>;

private:
  std::unordered_map<std::uint64_t, TruckPosition> trucks_;

  // Per subscription callback.
  std::unordered_map<std::uint64_t, Callback> callbacks_;

  // Per truck callbacks.
  std::unordered_map<std::uint64_t, std::list<decltype(callbacks_)::const_iterator>> perTruckCallbacks_;

  // Iterators per subscroption into the truck callbacks.
  std::unordered_map<
    std::uint64_t,
    std::unordered_map<std::uint64_t, decltype(perTruckCallbacks_)::value_type::second_type::const_iterator>>
    perSubCallbacks_;

  std::uint64_t nextId_{ 1 };

public:
  std::uint64_t connect_client(Callback cb)
  {
    if (auto ins = callbacks_.try_emplace(nextId_, std::move(cb)); !ins.second) {
      ins.first->second = std::move(cb);
    }
    return nextId_++;
  }

  void disconnect_client(const std::uint64_t cid)
  {
    if (auto it = perSubCallbacks_.find(cid); it != perSubCallbacks_.end()) {

      for (const auto& [truck, listIter] : it->second) {
        perTruckCallbacks_[truck].erase(listIter);
      }

      perSubCallbacks_.erase(it);
    }

    callbacks_.erase(cid);
  }

  void add_position(std::uint64_t truck_id, const TruckPosition& pos)
  {
    auto old = trucks_[truck_id];
    trucks_[truck_id] = pos;
    const TruckPositionDelta delta{ truck_id, pos.x - old.x, pos.y - old.y };

    const auto& callbacks = perTruckCallbacks_[truck_id];
    for (const auto& callback : callbacks)
      callback->second(delta);
  }

  void add_delta(std::uint64_t truck_id, const float dx, const float dy)
  {
    trucks_[truck_id].x += dx;
    trucks_[truck_id].y += dy;

    const TruckPositionDelta delta{ truck_id, dx, dy };

    const auto& callbacks = perTruckCallbacks_[truck_id];
    for (const auto& callback : callbacks)
      callback->second(delta);
  }

  TruckPosition subscribeToTruck(const std::uint64_t subID, const std::uint64_t truckID)
  {
    const auto finc = callbacks_.find(subID);
    if (finc == callbacks_.cend())
      throw std::runtime_error("No subscriber with this ID is known");

    auto& cbs = perSubCallbacks_[subID];
    if (const auto fid = cbs.find(truckID); fid != cbs.cend()) {
      // We don't need to subscribe again.
      return trucks_[truckID];
    }

    auto& truckCallbacks = perTruckCallbacks_[truckID];
    auto tid = truckCallbacks.insert(truckCallbacks.end(), finc);
    cbs.emplace(truckID, tid);

    return trucks_[truckID];
  }
};

class Subscriber
{
  Server& server_;
  std::uint64_t serverToken_;

  std::unordered_map<std::uint64_t, TruckPosition> trucks_;

  // TruckID -> clientIDs
  std::unordered_map<std::uint64_t, std::unordered_set<std::uint64_t>> truckToClients_;
  // clientID -> vector
  std::unordered_map<std::uint64_t, std::vector<TruckPositionDelta>> updates_;

  void update_callback(const TruckPositionDelta& delta)
  {
    auto& t = trucks_[delta.truck_id];
    t.x += delta.x;
    t.y += delta.y;

    for (const auto& client : truckToClients_[delta.truck_id]) {
      updates_[client].emplace_back(delta);
    }
  }

public:
  explicit Subscriber(Server& server) : server_{ server }
  {
    serverToken_ = server.connect_client([this](const auto& delta) { update_callback(delta); });
  }

  ~Subscriber() { server_.disconnect_client(serverToken_); }

  TruckPosition subscribe_to_truck(std::uint64_t clientID, std::uint64_t truckID)
  {
    auto [it, inserted] = truckToClients_.try_emplace(truckID);
    if (inserted) {
      trucks_[truckID] = server_.subscribeToTruck(serverToken_, truckID);
    }
    it->second.emplace(clientID);

    const auto& [x, y] = trucks_[truckID];

    std::cout << "S " << clientID << " " << truckID << " " << x << " " << y << std::endl;

    return trucks_[truckID];
  }

  std::vector<TruckPositionDelta> get_updates(const std::uint64_t clientID)
  {
    std::vector<TruckPositionDelta> ret;
    std::swap(ret, updates_[clientID]);

    return ret;
  }

  void printUpdates(const std::uint64_t clientID)
  {
    auto ans = get_updates(clientID);
    for (const auto& delta : ans) {
      std::cout << "U " << clientID << " " << delta.truck_id << " " << delta.x << " " << delta.y << std::endl;
    }
  }
};

int
main()
{
  Server srv;
  Subscriber sub(srv);

  srv.add_position(0, { 2, 3 });
  srv.add_delta(0, 1.5, 2.5);

  sub.subscribe_to_truck(0, 0);

  srv.add_delta(0, 1, 2);
  srv.add_delta(0, -0.5, -0.5);

  sub.subscribe_to_truck(1, 0);

  sub.printUpdates(0);

  srv.add_delta(0, 1, 1);

  sub.printUpdates(1);

  return 0;
}
