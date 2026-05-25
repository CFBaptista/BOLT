#include <array>
#include <cstddef>

namespace bolt
{

namespace lbm
{

/**
 * @brief A class template representing the D2Q9 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D2Q9
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D2Q9() = delete;
    ~D2Q9() = delete;
    D2Q9(const D2Q9& other) = delete;
    auto operator=(const D2Q9& other) -> D2Q9& = delete;
    D2Q9(D2Q9&& other) = delete;
    auto operator=(D2Q9&& other) -> D2Q9& = delete;

    /**
     * @brief The spatial dimension of the lattice model (2D).
     */
    static constexpr std::size_t dimension{2};
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 9;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0, 0}},
         {{1, 0}},
         {{0, 1}},
         {{-1, 0}},
         {{0, -1}},
         {{1, 1}},
         {{-1, 1}},
         {{-1, -1}},
         {{1, -1}}}

    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36), static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36)

    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

} // namespace lbm

} // namespace bolt
