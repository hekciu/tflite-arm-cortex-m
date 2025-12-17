#define TF_LITE_STATIC_MEMORY
// #define TF_LITE_STRIP_ERROR_STRINGS

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


// #include "sine_model.cc"
// #include "sine_model_stolen.h"

#include "sine_model.h"


#include "uart.hpp"
#include "led.hpp"


static void spin(uint32_t ticks) { while (ticks > 0) ticks--; };


const void* sine_model_data = (const void *)_home_hekciu_programming_embedded_ml_tflite_wb55_bare_metal____sine_wave_model_models_sine_model_tflite;
const uint32_t sine_model_size = _home_hekciu_programming_embedded_ml_tflite_wb55_bare_metal____sine_wave_model_models_sine_model_tflite_len;

// const void* sine_model_data = sine_model;
// const uint32_t sine_model_size = sine_model_len;



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

    MicroPrintf("dupa\n\r");

    // teraz tutaj sie wywala
    const auto debug_status = interpreter.AllocateTensors();

    TF_LITE_ENSURE_STATUS(debug_status);

    TfLiteTensor* input = interpreter.input(0);
    TFLITE_CHECK_NE(input, nullptr);

    TfLiteTensor* output = interpreter.output(0);
    TFLITE_CHECK_NE(output, nullptr);

    float output_scale = output->params.scale;
    int output_zero_point = output->params.zero_point;

    // Check if the predicted output is within a small range of the
    // expected output
    float epsilon = 0.05;

    constexpr int kNumTestValues = 4;
    float golden_inputs_float[kNumTestValues] = {0.77, 1.57, 2.3, 3.14};

    // The int8 values are calculated using the following formula
    // (golden_inputs_float[i] / input->params.scale + input->params.zero_point)
    int8_t golden_inputs_int8[kNumTestValues] = {-96, -63, -34, 0};

    int8_t output_values[kNumTestValues] = {};

    for (int i = 0; i < kNumTestValues; ++i) {
        input->data.int8[0] = golden_inputs_int8[i];
        TF_LITE_ENSURE_STATUS(interpreter.Invoke());
        // float y_pred = (output->data.int8[0] - output_zero_point) * output_scale;
        // TFLITE_CHECK_LE(abs(sin(golden_inputs_float[i]) - y_pred), epsilon);
        output_values[i] = output->data.int8[i];
    }

    MicroPrintf("test %d %d %d %d\n\r", output_values[0], output_values[1], output_values[2], output_values[3]);

    return kTfLiteOk;
}


void debug_log_printf(const char* s) {
    uart_transmit(s);
}


//__attribute__((naked, noreturn)) void _reset(void) {
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

    RegisterDebugLogCallback(debug_log_printf);

    /* This one does work */
    setup_green_led();
    uart_init(115200);

    /* This one does not */
    // setup_green_led();
    // uart_init(115200);

    for(;;) {
        main();

        blink_green_led();

        // va_list vl;

        //DebugLog("test\n\r", vl);

        // MicroPrintf("dupa MicroPrintf\n\r");

        //uart_transmit("dupa uart_transmit\r\n");

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


