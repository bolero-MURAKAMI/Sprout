#ifndef SPROUT_DARKROOM_CAMERAS_ANGLE_OF_VIEW_HPP
#define SPROUT_DARKROOM_CAMERAS_ANGLE_OF_VIEW_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/darkroom/coords/vector.hpp>

namespace sprout {
	namespace darkroom {
		namespace cameras {
			//
			// angle_of_view_reference
			//
			struct angle_of_view_reference {
			public:
				enum values {
					long_side,
					short_side,
					width,
					height
				};
			};
		}	// namespace cameras
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_CAMERAS_ANGLE_OF_VIEW_HPP
