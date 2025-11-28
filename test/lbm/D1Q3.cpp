#include "lbm/D1Q3.hpp"

#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

template <LatticeModel T>
class Foo
{
public:
    int foo = T::size();
};

constexpr Foo<D1Q3<float>> foo{};

static_assert(foo.foo == 3);

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D1Q3 lattice model properties")
{
    GIVEN("A D1Q3 lattice model")
    {
        using Model = D1Q3<float>;

        std::move_only_function<std::size_t()> model_dimension = &Model::dimension;
        std::move_only_function<std::size_t()> model_size = &Model::size;
        std::move_only_function<std::array<std::array<int, Model::dimension()>, Model::size()>()>
            model_velocities = &Model::velocities;
        std::move_only_function<std::array<float, Model::size()>()> model_weights = &Model::weights;

        const auto expectedDimension{1};
        const auto expectedSize{3};
        const auto expectedVelocities = std::array<std::array<int, 1>, 3>{
            std::array<int, 1>{0}, std::array<int, 1>{1}, std::array<int, 1>{-1}
        };
        const auto expectedWeights = std::array<float, 3>{4.0F / 6, 1.0F / 6, 1.0F / 6};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 1")
            {
                CHECK((dimension == expectedDimension));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 3")
            {
                CHECK((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 3 velocities are correct")
            {
                CHECK((velocities.size() == expectedVelocities.size()));
                CHECK((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                int sum{0};
                for (const auto& velocity : velocities)
                {
                    sum = std::accumulate(velocity.begin(), velocity.end(), sum);
                }

                CHECK((sum == 0));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 3 weights are correct")
            {
                CHECK((weights.size() == expectedWeights.size()));
                CHECK((weights == expectedWeights));
                CHECK((std::accumulate(weights.begin(), weights.end(), 0.0) == Catch::Approx(1.0)));
            }
        }
    }
}
