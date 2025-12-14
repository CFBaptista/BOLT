#pragma once

#include "lbm/NodeDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Velocity>
class DensityDistribution : public NodeDistributionBase
{
public:
    /// The velocity set type.
    using VelocityType = Velocity;
    /// The floating-point type.
    using Float = typename Velocity::Float;

    DensityDistribution() noexcept = default;
    explicit DensityDistribution(const Vector<Float, Velocity::size()>& distribution) noexcept;
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
    static constexpr auto dimension() noexcept -> Count;

    /**
     * @fn size
     *
     * @brief Returns the number of discrete velocity vectors of the velocity set.
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() noexcept -> Count;

    auto operator[](Count index) -> Float&;
    auto operator[](Count index) const -> const Float&;

    /**
     * @fn density
     *
     * @brief Returns the macroscopic density computed from the distribution function.
     *
     * @return The density.
     */
    auto density() const noexcept -> Float;

    /**
     * @fn momentum
     *
     * @brief Returns the macroscopic momentum computed from the distribution function.
     *
     * @return The momentum.
     */
    auto momentum() const noexcept -> Vector<Float, Velocity::dimension()>;

    /**
     * @fn velocity
     *
     * @brief Returns the macroscopic velocity computed from the distribution function.
     *
     * @return The velocity.
     */
    static auto velocity(const Float& density, const Vector<Float, Velocity::dimension()>& momentum)
        -> Vector<Float, Velocity::dimension()>;

private:
    /// The distribution function values at the lattice node.
    Vector<Float, Velocity::size()> distribution_;
};

#include "lbm/DensityDistribution.tpp"
