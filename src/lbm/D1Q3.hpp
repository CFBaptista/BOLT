#include <array>

#include <cstddef>

namespace bolt
{

namespace lbm
{

/**
 * @brief A class template representing the D1Q3 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D1Q3
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D1Q3() = delete;
    ~D1Q3() = delete;
    D1Q3(const D1Q3& other) = delete;
    auto operator=(const D1Q3& other) -> D1Q3& = delete;
    D1Q3(D1Q3&& other) = delete;
    auto operator=(D1Q3&& other) -> D1Q3& = delete;

    /**
     * @brief The spatial dimension of the lattice model (1D).
     */
    static constexpr std::size_t dimension = 1;
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 3;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0}}, {{1}}, {{-1}}}
    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(6), static_cast<Real>(1) / static_cast<Real>(6),
        static_cast<Real>(1) / static_cast<Real>(6)
    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

} // namespace lbm

} // namespace bolt
