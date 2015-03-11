#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "../LCG-PLE63/std_LCG_PLE63.hpp"
#include "../LCG-PLE63/uniform_distribution.hpp"
#include "Spectrum.hpp"

int main(int argc, char* argv[])
{
    std::linear_congruential_engine<uint64_t, 2806196910506780709ULL, 1ULL, (1ULL<<63ULL)> ugen;
    std::uniform_distribution<float>                                                       rng;

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
        double e = s.sample(rng(ugen), rng(ugen));

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
