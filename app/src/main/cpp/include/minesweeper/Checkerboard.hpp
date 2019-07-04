//
// Created by peter on 19-5-20.
//

#ifndef MINESWEEPER_CHECKERBOARD_HPP
#define MINESWEEPER_CHECKERBOARD_HPP

#include <set>
#include <utility>
#include <boost/multi_array.hpp>
#include "ClickResult.hpp"

namespace minesweeper
{
	class Checkerboard
	{
		public:
			using coordinate_type = int;
			using mine_set_type = std::set<std::pair<coordinate_type, coordinate_type>>;
			using checker_board_type = boost::multi_array<int, 2>;
			using size_type = size_t;

			static constexpr const int INIT = -1;
			static constexpr const int MINE = -2;
			static constexpr const int FLAG = -3;


		private:
			coordinate_type height; ///< height of the checkerboard
			coordinate_type width; ///< width of the checkerboard
			mine_set_type mine_set; ///< set of the coordinate of the grids contain mine
			const size_type mine_num;
			checker_board_type checker_board;
			bool has_init = false;

		public:
			Checkerboard(coordinate_type height, coordinate_type width);
			Checkerboard(coordinate_type height, coordinate_type width, size_type mine_num);

			coordinate_type get_width() const
			{
				return width;
			}

			coordinate_type get_height() const
			{
				return height;
			}

			size_type get_mine_num() const
			{
				return mine_num;
			}

			checker_board_type get_uncovered_checkerboard_detail() const;

			const checker_board_type& get_covered_checkerboard_detail() const;

			ClickResult click_on(coordinate_type click_x, coordinate_type click_y);

			ClickResult set_flag(coordinate_type click_x, coordinate_type click_y);

			bool is_in_bound(coordinate_type x, coordinate_type y) const;

			size_type get_mine_count_nearby(int x, int y) const;

	};
}


#endif //MINESWEEPER_CHECKERBOARD_HPP
