#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "lcg63.h"
#include "Spectrum.hpp"

int main(int argc, char* argv[])
{
    TOK::lcg63 rng;

    Spectrum s("spectrum.dat");

    std::cout << std::scientific;
    for(int k = -1; k != s.nof_bins(); ++k)
    {
        int i = k+1;
        std::cout << std::setw(15) << std::setprecision(4)
                  << s.pos()[i]
                  << std::setw(15) << std::setprecision(4)
                  << s.prb()[i]
                  << std::endl;
    }
    std::cout << std::endl;

    // one underflow bin and one overflow bin
    std::vector<uint32_t> histo(s.pos().size()+1, 0);

    const uint64_t N = 500000000;

    for(uint64_t k = 0; k != N; ++k)
    {
        double e = s.sample(rng.number(), rng.number());

        int idx = (std::lower_bound(s.pos().cbegin(), s.pos().cend(), e) - s.pos().cbegin());
        histo[idx] += 1;
    }

    int k = -1;
    for(auto x: histo)
    {
        double bl = 0.0;
        if (k != -1)
            bl = s.pos()[k];
        ++k;
        double br = s.pos()[k];

        double t = (bl + br)/2.0;
        double v = double(x) * s.norm() / double(N);
        std::cout << std::scientific << std::setw(15) << std::setprecision(4) << t
                  // << std::scientific << std::setw(15) << std::setprecision(4) << br
                  << std::scientific << std::setw(15) << std::setprecision(4) << v
                  << std::endl;
    }

    return 0;
}
