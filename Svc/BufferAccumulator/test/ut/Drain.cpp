// ======================================================================
// \title  Drain.hpp
// \author bocchino, mereweth
// \brief  Test drain mode
//
// \copyright
// Copyright (c) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <string.h>

#include "Drain.hpp"

namespace Svc {

  namespace Drain {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void Tester ::
      OK(void)
    {
      ASSERT_EQ(BufferAccumulator::DRAIN, this->component.mode);
      Fw::Buffer buffers[MAX_NUM_BUFFERS];
      U8* data = new U8[10*sizeof(U32)];
      const U32 size = 10;
      for (U32 i = 0; i < MAX_NUM_BUFFERS; ++i) {
        ASSERT_from_bufferSendOutDrain_SIZE(i);
        const U32 bufferID = i;
        Fw::Buffer b(data, size, bufferID);
        buffers[i] = b;
        this->invoke_to_bufferSendInFill(0, buffers[i]);
        this->component.doDispatch();
        ASSERT_from_bufferSendOutDrain_SIZE(i + 1);
        ASSERT_from_bufferSendOutDrain(i, buffers[i]);
        this->invoke_to_bufferSendInReturn(0, buffers[i]);
        this->component.doDispatch();
        ASSERT_from_bufferSendOutReturn(i, buffers[i]);
      }

      delete[] data;
    }

  }

}
