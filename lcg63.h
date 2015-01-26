// -*- C++ -*-

#pragma once

#include <cstdint>

#define LCG63_NORM 1.0842021724855044340074528008699e-19 // 1/2^63

namespace TOK
{
    class lcg63
    {
        public: typedef uint64_t seed_type;

        public: static const seed_type nbits  = 63ULL;
        public: static const seed_type mod    = 1ULL << nbits;
        public: static const seed_type mask   = mod - 1ULL;

        // those values are taken from
        // P.L'Ecuyer "Efficient and Portable Combined RNGs",
        // Comm.ACM 31(6): 742-749, 774 (1988)
        public: static const seed_type mult   = 2806196910506780709ULL;
        public: static const seed_type add    = 1ULL;

#pragma region Data
        private: mutable seed_type _seed;
#pragma endregion

#pragma region Ctor/Dtor/op=
        public: lcg63():
            _seed(1ULL)
        {
        }

        public: lcg63(uint64_t seed):
            _seed(seed)
        {
        }

        public: lcg63(const lcg63& r):
            _seed(r._seed)
        {
        }

        public: lcg63& operator=(const lcg63& r)
        {
            _seed = r._seed;
            return *this;
        }

        public: ~lcg63()
        {
        }
#pragma endregion

#pragma region Observers
        public: seed_type seed() const
        {
            return _seed;
        }
#pragma endregion

#pragma region Helpers

        // compute and return positive skip
        public: static int64_t compute_nskip(int64_t ns);

        // could skip forward as well as backward
        public: static seed_type skip(int64_t ns, seed_type seed);

#pragma endregion

#pragma region Mutators
        public: void sample() const
        {
            _seed = (mult * _seed + add) & mask;
        }

        public: float number() const
        {
            sample();
            return float(_seed)*float(LCG63_NORM);
        }

        public: void skip(int64_t ns) const
        {
            _seed = skip(ns, _seed);
        }
#pragma endregion
    };
}
