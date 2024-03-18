#include <iostream>
#include <limits>
#include <vector>
#include <cstdint>
#include <algorithm>

struct Request {
	std::uint32_t artist_id;
	std::uint32_t location_id;

	std::uint32_t ticket_price;
	std::uint32_t category;
	std::uint32_t available_seats;

	Request(std::uint32_t artist, std::uint32_t location, std::uint32_t ticket_price,
			std::uint32_t cat, std::uint32_t available_seats) : 
		artist_id{artist}, location_id{location}, ticket_price{ticket_price},
		category{cat}, available_seats{available_seats} {}

};

struct Available {
public:
	std::uint32_t message_id{0};
	std::uint32_t artist_id{0};
	std::uint32_t location_id{0};

	std::uint32_t ticket_price{std::numeric_limits<std::uint32_t>::max()};
	std::uint32_t category{0};
	std::uint32_t available_seats{1};


	Available(std::uint32_t message, std::uint32_t artist) : message_id{message}, artist_id{artist} {}

	[[nodiscard]] constexpr bool update(const std::uint32_t data) {
		switch (step_) {
			case 0:
				location_id = data; break;
			case 1:
				ticket_price = data; break;
			case 2:
				category = data; break;
			case 3:
				available_seats = data; break;
			default:
				return true;
		}

		step_++;
		return step_ == 4;
	}

	[[nodiscard]] constexpr bool matches(const Request& req) {
		// We need to know the location before.
		if (step_ < 1)
			return false;

		if (artist_id != req.artist_id)
			return false;

		if (location_id != req.location_id)
			return false;

		if (req.ticket_price < ticket_price)
			return false;

		if (category < req.category )
			return false;

		if (available_seats < req.available_seats)
			return false;

	
		return true;
	}


private:
	// How many data fields have we seen.
	std::uint8_t step_{0};
};

class ConcertBuyer {

	// This is setup with the assumption that there will be less than 1000 items in
	// flight at one time. At this scale the memory overhead with a map will be larger
	// than just scanning through the vector linearly. For a larger number we could employ
	// a flat_map or something like google swiss tables to get a similar effect.
	std::vector<Available> inflight_;

	// The same goes for the requests. We will try every request on every new update.
	// This could be optimized by something like a plain sort on the artist_id. or a store
	// in a flat map.
	std::vector<Request> requests_;

	public:


	constexpr void on_new_requirement(const std::uint32_t artist_id, const std::uint32_t location_id,
			std::uint32_t ticket_price, std::uint32_t category, std::uint32_t available_sets) {
		requests_.emplace_back(artist_id, location_id, ticket_price, category, available_sets);
	}


	void process_data(const std::uint32_t message_id, const std::uint32_t data) {
		if (message_id == 0) {
			std::cout << "0\n";
			return;
		}

		// First of we search for the message ID in our in flights.
		for (auto avIt =  inflight_.begin(); avIt != inflight_.end(); avIt++) {
			if (avIt->message_id != message_id)
				continue;
			/* std::cout << "We are here!" << std::endl; */

			bool finished = avIt->update(data);
			bool sentData = false;
			for (auto reqIt = requests_.begin(); reqIt != requests_.end(); reqIt++) {
				if (avIt->matches(*reqIt)) {
					finished = true;
					sentData = true;
					std::cout << avIt->message_id << '\n' << reqIt->available_seats << '\n';

					std::iter_swap(reqIt, requests_.end()-1);
					requests_.pop_back();

					break;
				}
			}

			if (finished) {
				/* std::cout << "We came here with:!" << std::endl; */
				/* std::cout << avIt->message_id << " " << avIt->artist_id << " " << avIt->location_id << " " */
				/* 	<< avIt->ticket_price << " " << avIt->category << " " << avIt->available_seats << std::endl; */
				std::iter_swap(avIt, inflight_.end()-1);
				inflight_.pop_back();
			}
			
			if (!sentData) {
				std::cout << "0\n";
			}
			return;
		}

		// We didn't find anything, so we must insert it.
		inflight_.emplace_back(message_id, data);
		/* std::cout << "0\n0\n"; */
		std::cout << "0\n";
	}
};

int main() {
	ConcertBuyer cb;

	cb.on_new_requirement(1, 1, 100, 1, 2);
	cb.on_new_requirement(1, 1, 100, 1, 2);

	cb.process_data(1, 1);
	cb.process_data(1, 1);
	cb.process_data(1, 110);
	cb.process_data(1, 3);
	cb.process_data(1, 3);
	cb.process_data(0, 0);

	cb.process_data(3, 1);

	cb.process_data(2, 1);
	cb.process_data(2, 1);
	cb.process_data(3, 1);
	cb.process_data(2, 90);
	cb.process_data(2, 3);
	cb.process_data(2, 3);
	cb.process_data(3, 90);
	cb.process_data(3, 3);
	cb.process_data(3, 3);

	cb.process_data(0, 0);
	cb.process_data(0, 0);
	cb.process_data(0, 0);
	cb.process_data(0, 0);


	return 0;
}
