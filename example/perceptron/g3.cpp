/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/algorithm/copy.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/math/sigmoid.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/random/generate_array.hpp>
#include <sprout/assert.hpp>

//
// perceptron
//
template<typename FloatType, std::size_t In, std::size_t Hid, std::size_t Out>
class perceptron {
public:
	typedef FloatType value_type;
private:
	struct worker {
	public:
		// in
		sprout::array<value_type, In + 1> xi1;
		sprout::array<value_type, Hid + 1> xi2;
		sprout::array<value_type, Out> xi3;
		// out
		sprout::array<value_type, In + 1> o1;
		sprout::array<value_type, Hid + 1> o2;
		sprout::array<value_type, Out> o3;
	};
private:
	// error
	sprout::array<value_type, Hid + 1> d2;
	sprout::array<value_type, Out> d3;
	// weight
	sprout::array<value_type, (In + 1) * Hid> w1;
	sprout::array<value_type, (Hid + 1) * Out> w2;
private:
	// forward propagation
	template<typename ForwardIterator>
	SPROUT_CXX14_CONSTEXPR void
	forward_propagation(ForwardIterator in_first, ForwardIterator in_last, worker& work) const {
		// forward propagation with input layer
		sprout::copy(in_first, in_last, sprout::begin(work.xi1));
		work.xi1[In] = 1;
		sprout::copy(sprout::begin(work.xi1), sprout::end(work.xi1), sprout::begin(work.o1));

		// forward propagation with hidden layer
		for (std::size_t i = 0; i != Hid; ++i) {
			work.xi2[i] = 0;
			for (std::size_t j = 0; j != In + 1; ++j) {
				work.xi2[i] += w1[j * Hid + i] * work.o1[j];
			}
			work.o2[i] = sprout::math::sigmoid(work.xi2[i]);
		}
		work.o2[Hid] = 1;

		// forward propagation with output layer
		for (std::size_t i = 0; i != Hid; ++i) {
			work.xi3[i] = 0;
			for (std::size_t j = 0; j != In + 1; ++j) {
				work.xi3[i] += w2[j * Out + i] * work.o2[j];
			}
			work.o3[i] = work.xi3[i];
		}
	}
public:
	template<typename RandomNumberGenerator>
	explicit SPROUT_CXX14_CONSTEXPR perceptron(RandomNumberGenerator& rng)
		: d2{{}}, d3{{}}
		, w1(sprout::random::generate_array<(In + 1) * Hid>(rng, sprout::random::uniform_01<value_type>()))
		, w2(sprout::random::generate_array<(Hid + 1) * Out>(rng, sprout::random::uniform_01<value_type>()))
	{}

	// training of neural network
	//	[in_first, in_last)	: training data (N*In elements)
	//	[t_first, t_last)	: training data (N elements)
	template<typename ForwardIterator1, typename ForwardIterator2>
	SPROUT_CXX14_CONSTEXPR void
	train(
		ForwardIterator1 in_first, ForwardIterator1 in_last,
		ForwardIterator2 t_first, ForwardIterator2 t_last,
		std::size_t repeat = 1000, value_type eta = value_type(0.1)
		)
	{
		SPROUT_ASSERT(sprout::distance(in_first, in_last) % In == 0);
		SPROUT_ASSERT(sprout::distance(in_first, in_last) / In == sprout::distance(t_first, t_last));

		worker work{};
		for (std::size_t times = 0; times != repeat; ++times) {
			ForwardIterator1 in_it = in_first;
			ForwardIterator2 t_it = t_first;
			for (; in_it != in_last; sprout::advance(in_it, In), ++t_it) {
				// forward propagation
				forward_propagation(in_it, sprout::next(in_it, In), work);

				// error calculation of output layer
				for (std::size_t i = 0; i != Out; ++i) {
					d3[i] = *t_it == i ? work.o3[i] - 1
						: work.o3[i]
						;
				}

				// weight update of output layer
				for (std::size_t i = 0; i != Hid + 1; ++i) {
					for (std::size_t j = 0; j != Out; ++j) {
						w2[i * Out + j] -= eta * d3[j] * work.o2[i];
					}
				}

				// error calculation of hidden layer
				for (std::size_t i = 0; i != Hid + 1; ++i) {
					d2[i] = 0;
					for (std::size_t j = 0; j != Out; ++j) {
						d2[i] += w2[i * Out + j] * d3[j];
					}
					d2[i] *= sprout::math::d_sigmoid(work.xi2[i]);
				}

				// weight update of hidden layer
				for (std::size_t i = 0; i != In + 1; ++i) {
					for (std::size_t j = 0; j != Hid; ++j) {
						w1[i * Hid + j] -= eta * d2[j] * work.o1[i];
					}
				}
			}
		}
	}

	// returns to predict the most likely class for a given data
	template<typename ForwardIterator>
	SPROUT_CXX14_CONSTEXPR std::size_t
	predict(ForwardIterator in_first, ForwardIterator in_last) const {
		SPROUT_ASSERT(sprout::distance(in_first, in_last) == In);

		worker work{};

		// prediction by forward propagation
		forward_propagation(in_first, in_last, work);

		// determining a class which output is maximum
		return sprout::distance(
			sprout::begin(work.o3),
			sprout::max_element(sprout::begin(work.o3), sprout::end(work.o3))
			);
	}
};

#include <cstddef>
#include <iostream>
#include <sprout/config.hpp>
#include <sprout/random/default_random_engine.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/static_assert.hpp>

// training data
SPROUT_CONSTEXPR auto train_data = sprout::make_array<double>(
#	include "g3_train.csv"
	);
// teaching data
SPROUT_CONSTEXPR auto teach_data = sprout::make_array<std::size_t>(
#	include "g3_teach.csv"
	);

SPROUT_STATIC_ASSERT(train_data.size() % 2 == 0);
SPROUT_STATIC_ASSERT(train_data.size() / 2 == teach_data.size());

// generate a trained perceptron
template<typename FloatType, std::size_t In, std::size_t Hid, std::size_t Out>
SPROUT_CXX14_CONSTEXPR ::perceptron<FloatType, In, Hid, Out>
make_trained_perceptron() {
	// random number generator
	sprout::random::default_random_engine rng(SPROUT_UNIQUE_SEED);

	// perceptron
	::perceptron<FloatType, In, Hid, Out> per(rng);

	// training
	per.train(
		train_data.begin(), train_data.end(),
		teach_data.begin(), teach_data.end(),
		500, 0.1
		);

	return per;
}

int main() {
	// generate a Perceptron (input 2, hidden 3, output 3)
	SPROUT_CXX14_CONSTEXPR auto per = ::make_trained_perceptron<double, 2, 3, 3>();

	// print results
	for (auto it = train_data.begin(), last = train_data.end(); it != last; it += 2) {
		std::cout << per.predict(it, it + 2) << std::endl;
	}
}
