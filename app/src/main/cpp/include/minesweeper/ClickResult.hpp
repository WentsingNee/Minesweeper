//
// Created by peter on 19-5-20.
//

#ifndef MINESWEEPER_CLICKRESULT_HPP
#define MINESWEEPER_CLICKRESULT_HPP

namespace minesweeper
{

	struct ClickResult
	{
			int x;
			int y;

			enum class ClickEventCategory
			{
					click_on_disable_area,
					click_on_valid_area,
					click_on_out_of_range_area,
					click_on_mine,
					set_flag,
					remove_flag,
					success,
			} click_event_category;

			ClickResult() noexcept = default;
	};
}

#endif //MINESWEEPER_CLICKRESULT_HPP
