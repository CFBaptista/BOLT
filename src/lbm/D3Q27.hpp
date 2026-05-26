#include <array>
#include <concepts>
#include <cstddef>

namespace bolt
{

namespace lbm
{

/**
 * @brief A class template representing the D3Q27 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D3Q27
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D3Q27() = delete;
    ~D3Q27() = delete;
    D3Q27(const D3Q27& other) = delete;
    auto operator=(const D3Q27& other) -> D3Q27& = delete;
    D3Q27(D3Q27&& other) = delete;
    auto operator=(D3Q27&& other) -> D3Q27& = delete;

    /**
     * @brief The spatial dimension of the lattice model (3D).
     */
    static constexpr std::size_t dimension = 3;
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 27;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}

    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(8) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216)

    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

} // namespace lbm

} // namespace bolt
