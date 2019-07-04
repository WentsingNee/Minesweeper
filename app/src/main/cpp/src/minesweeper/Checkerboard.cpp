//
// Created by peter on 19-5-20.
//

#include "minesweeper/Checkerboard.hpp"

#include <random>
#include <queue>
#include <chrono>

#include "Log.hpp"

namespace minesweeper
{
	Checkerboard::Checkerboard(coordinate_type height, coordinate_type width) :
			Checkerboard(height, width, height * width / 10)
	{
	}

	Checkerboard::Checkerboard(coordinate_type height, coordinate_type width, size_type mine_num) :
			height(height), width(width), mine_num(mine_num),
			checker_board(boost::extents[height][width]), has_init(false)
	{
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				checker_board[i][j] = Checkerboard::INIT;
			}
		}
	}
	Checkerboard::checker_board_type Checkerboard::get_uncovered_checkerboard_detail() const
	{
		coordinate_type height = this->get_height();
		coordinate_type width = this->get_width();
		checker_board_type v(boost::extents[height][width]);
		for (int x = 0; x < height; ++x) {
			for (int y = 0; y < width; ++y) {
				if (mine_set.find({ x, y }) != mine_set.cend()) {
					v[x][y] = Checkerboard::MINE;
					continue;
				}
				v[x][y] = this->get_mine_count_nearby(x, y);
			}
		}
		return v;
	}

	const Checkerboard::checker_board_type &
	Checkerboard::get_covered_checkerboard_detail() const
	{
		return this->checker_board;
	}

	ClickResult
	Checkerboard::click_on(coordinate_type click_x, coordinate_type click_y)
	{
		if (this->is_in_bound(click_x, click_y) == false) {
			return ClickResult{click_x, click_y, ClickResult::ClickEventCategory::click_on_out_of_range_area};
		}
		coordinate_type height = this->get_height();
		coordinate_type width = this->get_width();
		if (this->has_init == false) {
			this->has_init = true;
			std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
			std::uniform_int_distribution<int> x_distri(0, height - 1);
			std::uniform_int_distribution<int> y_distri(0, width - 1);

			while (this->mine_set.size() < mine_num) {
				const auto &[x, y] = std::pair {x_distri(generator), y_distri(generator)};
				if (std::pair { x, y } != std::pair { click_x, click_y }) {
					this->mine_set.insert( { x, y });
				}
			}
		}
		if (checker_board[click_x][click_y] != Checkerboard::INIT) {
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::click_on_disable_area };
		}
		if (mine_set.count({ click_x, click_y }) == true) { // boom
			checker_board[click_x][click_y] = Checkerboard::MINE;
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::click_on_mine };
		}
		boost::multi_array<bool, 2> vis(boost::extents[height][width]);
		std::queue<std::pair<int, int>> q;
		q.push( { click_x, click_y });
		vis[click_x][click_y] = true;
		while (!q.empty()) {
			const auto [x, y] = q.front();
			q.pop();
			checker_board[x][y] = this->get_mine_count_nearby(x, y);

			for (const auto & [x0, y0] :
						{
										   std::pair{x - 1, y},
								std::pair{x, y - 1},     std::pair{x, y + 1},
										   std::pair{x + 1, y},
						})
			{
				if (this->is_in_bound(x0, y0) and
						mine_set.find({x0, y0}) == mine_set.cend() and
						vis[x0][y0] == false and
						checker_board[x0][y0] == Checkerboard::INIT) {
					if (checker_board[x][y] == 0 and
							(checker_board[x0][y0] == 0 or checker_board[x0][y0] == Checkerboard::INIT)) {
						q.push( {	x0, y0});
						vis[x0][y0] = true;
					}
				}
			}
		}
		int uncovered_grid_count = 0;
		{
			for (int x = 0; x < height; ++x) {
				for (int y = 0; y < width; ++y) {
					if (this->checker_board[x][y] == Checkerboard::FLAG or
						this->checker_board[x][y] == Checkerboard::INIT)
					{
						++uncovered_grid_count;
					}
				}
			}
		}
		if (uncovered_grid_count == this->mine_num) {
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::success };
		} else {
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::click_on_valid_area };
		}
	}

	ClickResult
	Checkerboard::set_flag(coordinate_type click_x, coordinate_type click_y)
	{
		if (this->is_in_bound(click_x, click_y) == false) {
			return ClickResult{click_x, click_y, ClickResult::ClickEventCategory::click_on_out_of_range_area};
		}
		coordinate_type height = this->get_height();
		coordinate_type width = this->get_width();

		if (checker_board[click_x][click_y] == Checkerboard::FLAG) {
			checker_board[click_x][click_y] = Checkerboard::INIT;
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::remove_flag };
		}
		if (checker_board[click_x][click_y] != Checkerboard::INIT) {
			return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::click_on_disable_area };
		}

		checker_board[click_x][click_y] = Checkerboard::FLAG;
		return ClickResult { click_x, click_y, ClickResult::ClickEventCategory::set_flag };
	}

	bool Checkerboard::is_in_bound(coordinate_type x, coordinate_type y) const
	{
		if (0 <= x and x < height and
			0 <= y and y < width) {
			return true;
		} else {
			return false;
		}
	}

	Checkerboard::size_type
	Checkerboard::get_mine_count_nearby(int x, int y) const
	{
		int c = 0;
		for (const auto & [x0, y0] : {
				std::pair{x - 1, y - 1}, std::pair{x - 1, y}, std::pair{x - 1, y + 1},
				std::pair{x, y - 1},                          std::pair{x, y + 1},
				std::pair{x + 1, y - 1}, std::pair{x + 1, y}, std::pair{x + 1, y + 1},
		}) {
			if (this->is_in_bound(x0, y0) and
				mine_set.find({x0, y0}) != mine_set.cend())
			{
				++c;
			}
		}
		return c;
	}

}
