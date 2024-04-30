#include <spec/metrics.h>
#include <spec/conversions.h>
#include <internal/common/constants.h>
#include <cassert>

namespace spec::metrics {

    Float cie_delta_e(const vec3 &y1, const vec3 &y2)
    {
        return vec3::distance(rgb2cielab(y1), rgb2cielab(y2));
    }

    Float mae(const ISpectrum &y1, const ISpectrum &y2)
    {
        Float res = 0.0f;
        for(int wl = CURVES_WAVELENGHTS_START; wl <= CURVES_WAVELENGHTS_END; wl += CURVES_WAVELENGHTS_STEP) {
            res += std::fabs(y1(wl) - y2(wl));
        }
        return res / Float((CURVES_WAVELENGHTS_END - CURVES_WAVELENGHTS_START) / CURVES_WAVELENGHTS_STEP);
    }

    Float sam(const ISpectrum &y1, const ISpectrum &y2)
    {
        Float dist1 = 0.0f;
        Float dist2 = 0.0f;
        Float dot = 0.0f;
        for(int wl = CURVES_WAVELENGHTS_START; wl <= CURVES_WAVELENGHTS_END; wl += CURVES_WAVELENGHTS_STEP)
        {
            const Float val1 = y1(wl);
            dist1 += val1 * val1;
            const Float val2 = y2(wl);
            dist2 += val2 * val2;
            dot += val1 * val2;
        }
        const Float mdist = std::sqrt(dist1) * std::sqrt(dist2);
        return std::acos(dot / mdist);
    }

    Float mse(const Image &y1, const Image &y2)
    {
        assert(y1.get_width() == y2.get_width() && y1.get_height() == y2.get_height());

        Float res = 0.0f;
        const Pixel *raw1 = y1.raw_data();
        const Pixel *raw2 = y2.raw_data();
        const unsigned sz = y1.get_width() * y1.get_height();
        for(unsigned i = 0; i < sz; ++i) {
            res += vec3::distance2(raw1[i].to_vec3(), raw2[i].to_vec3()); 
        }
        return res / sz;
    }

    Float psnr(const Image &y1, const Image &y2)
    {
        return 10.0f * std::log10(3.0f / mse(y1, y2));
    }

    Float ssim(const Image &y1, const Image &y2)
    {
        (void) y1; (void) y2;
        return 1.0f;//TODO
    }

}