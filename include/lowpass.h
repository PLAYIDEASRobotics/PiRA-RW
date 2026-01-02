#pragma once

#include <cmath>

#include "vex.h"

namespace CheckLib{

  class LowPassFilter{

  private:
    vex::timer m_timer;

    double m_RC;
    double m_output;

  public:
    LowPassFilter(double rc){
      m_RC = fmax(rc, 0.0000001);
      m_output = 0;
    }

    double get(double next){
      double dT = m_timer.time(vex::sec);
      m_timer.reset();

      double a = 1.0 - exp(-dT / m_RC);
      m_output += (next - m_output) * a;

      return m_output;
    }

  };

}