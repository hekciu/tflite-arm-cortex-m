#define TF_LITE_STATIC_MEMORY

#include <math.h>

#include "tensorflow/lite/core/c/common.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_allocator.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_profiler.h"
#include "tflite-micro/tensorflow/lite/micro/micro_interpreter_graph.h"
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tflite-micro/tensorflow/lite/micro/memory_helpers.h"
#include "tflite-micro/tensorflow/lite/micro/micro_arena_constants.h"
#include "tensorflow/lite/micro/memory_planner/greedy_memory_planner.h"
#include "tensorflow/lite/micro/memory_planner/linear_memory_planner.h"
#include "tensorflow/lite/micro/memory_planner/micro_memory_planner.h"

#include "tensorflow/lite/micro/cortex_m_generic/debug_log_callback.h"
#include "tflite-micro/tensorflow/lite/micro/debug_log.h"


#include "sine_model.h"


#include "uart.hpp"



const void* sine_model_data = model;
const uint32_t sine_model_size = model_len;

static void spin(uint32_t ticks) { while (ticks > 0) ticks--; };

static constexpr int kTensorArenaSize = 100000;


namespace {
    using HelloWorldOpResolver = tflite::MicroMutableOpResolver<1>;

    TfLiteStatus RegisterOps(HelloWorldOpResolver& op_resolver) {
      TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
      return kTfLiteOk;
    }
}

int main(void) {
    tflite::InitializeTarget();

    HelloWorldOpResolver op_resolver;
    TF_LITE_ENSURE_STATUS(RegisterOps(op_resolver));

    constexpr int kTensorArenaSize = 3000;
    uint8_t tensor_arena[kTensorArenaSize];
    constexpr int kNumResourceVariables = 24;

    tflite::RecordingMicroAllocator* allocator(
        tflite::RecordingMicroAllocator::Create(tensor_arena, kTensorArenaSize));
    tflite::RecordingMicroInterpreter interpreter(
        tflite::GetModel(sine_model_data), op_resolver, allocator,
        tflite::MicroResourceVariables::Create(allocator, kNumResourceVariables));

    const auto debug_status = interpreter.AllocateTensors();

    TF_LITE_ENSURE_STATUS(debug_status);

    TfLiteTensor* input = interpreter.input(0);
    TFLITE_CHECK_NE(input, nullptr);

    TfLiteTensor* output = interpreter.output(0);
    TFLITE_CHECK_NE(output, nullptr);

    float output_scale = output->params.scale;
    int output_zero_point = output->params.zero_point;

    constexpr int kNumTestValues = 4;
    float golden_inputs_float[kNumTestValues] = {0.77, 1.57, 2.3, 3.14};

    // The int8 values are calculated using the following formula
    // (golden_inputs_float[i] / input->params.scale + input->params.zero_point)
    int8_t golden_inputs_int8[kNumTestValues] = {-96, -63, -34, 0};

    int8_t output_values[kNumTestValues] = {};

    for (int i = 0; i < kNumTestValues; ++i) {
        input->data.int8[0] = golden_inputs_int8[i];
        TF_LITE_ENSURE_STATUS(interpreter.Invoke());
        output_values[i] = output->data.int8[i];
    }

    MicroPrintf("output values %d %d %d %d\n\r", output_values[0], output_values[1], output_values[2], output_values[3]);

    return kTfLiteOk;
}


extern "C" __attribute__((naked, noreturn)) void Reset_Handler(void) {
    extern long _sdata, _edata, _sbss, _ebss, _sidata;

    for (long* bss_el = &_sbss; bss_el < &_ebss; bss_el++) {
        *bss_el = 0;
    }

    for (long *dst_el = &_sdata, *src_el = &_sidata; dst_el < &_edata;) {
        *dst_el = *src_el;
        dst_el++;
        src_el++;
    }

    RegisterDebugLogCallback(uart_transmit);

    uart_init(115200);

    for(;;) {
        main();

        spin(99999);
    }
}


extern "C" void _estack(void);  // Defined in link.ld

// 16 standard and 63 STM32WB55-specific handlers
extern "C" __attribute__((section(".vectors"))) void (*const tab[16 + 63])(void) = {
  _estack, Reset_Handler, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};


