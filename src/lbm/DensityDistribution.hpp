#pragma once

#include "lbm/NodeDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Set>
class DensityDistribution : public NodeDistributionBase
{
public:
    /// The floating-point type.
    using Float = typename Set::Float;

    DensityDistribution() noexcept = default;
    explicit DensityDistribution(const Vector<Float, Set::size()>& distribution) noexcept;
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
    auto momentum() const noexcept -> Vector<Float, Set::dimension()>;

    /**
     * @fn velocity
     *
     * @brief Returns the macroscopic velocity computed from the distribution function.
     *
     * @return The velocity.
     */
    static auto velocity(const Float& density, const Vector<Float, Set::dimension()>& momentum)
        -> Vector<Float, Set::dimension()>;

private:
    /// The distribution function values at the lattice node.
    Vector<Float, Set::size()> distribution_;
};

#include "lbm/DensityDistribution.tpp"
