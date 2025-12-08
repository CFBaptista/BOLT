#pragma once

#include <array>
#include <cstddef>

#include "lbm/NodeDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set>
class DensityDistribution : public NodeDistributionBase
{
public:
    /// The floating-point type.
    using Real = typename Set::Real;

    DensityDistribution() noexcept = default;
    explicit DensityDistribution(const std::array<Real, Set::size()>& distribution) noexcept;
    DensityDistribution(const DensityDistribution& other) noexcept = default;
    DensityDistribution(DensityDistribution&& other) noexcept = default;
    auto operator=(const DensityDistribution& other) noexcept -> DensityDistribution& = default;
    auto operator=(DensityDistribution&& other) noexcept -> DensityDistribution& = default;
    ~DensityDistribution() noexcept = default;

    /**
     * @fn dimension
     *
     * @brief Returns the spatial dimension of the velocity set.
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() noexcept -> std::size_t;

    /**
     * @fn size
     *
     * @brief Returns the number of discrete velocity vectors of the velocity set.
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() noexcept -> std::size_t;

    auto operator[](std::size_t index) -> Real&;
    auto operator[](std::size_t index) const -> const Real&;

    /**
     * @fn density
     *
     * @brief Returns the macroscopic density computed from the distribution function.
     *
     * @return The density.
     */
    auto density() const noexcept -> Real;

    /**
     * @fn momentum
     *
     * @brief Returns the macroscopic momentum computed from the distribution function.
     *
     * @return The momentum.
     */
    auto momentum() const noexcept -> std::array<Real, Set::dimension()>;

    /**
     * @fn velocity
     *
     * @brief Returns the macroscopic velocity computed from the distribution function.
     *
     * @return The velocity.
     */
    auto velocity(const Real& density, const std::array<Real, Set::dimension()>& momentum) const
        -> std::array<Real, Set::dimension()>;

private:
    /// The distribution function values at the lattice node.
    std::array<Real, Set::size()> distribution_;
};

#include "lbm/DensityDistribution.tpp"
