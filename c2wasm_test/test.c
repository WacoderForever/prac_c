#include "c2wasm.c"
#include <stdio.h>

long set_div_value() {
  // Create an array to hold function arguments
  c2wasm_js_var find_args = c2wasm_create_array();
  c2wasm_append_array_string(find_args, "test_div");
  
  // Get the DOM element with id "test_div"
  c2wasm_js_var element = c2wasm_call_object_prop(c2wasm_document, "getElementById", find_args);  
  
  // Set the innerHTML of the element
  c2wasm_set_object_prop_string(element, "innerHTML", "Hello World from C");
  
  return c2wasm_undefined;
}

int main() {
  // Initialize C2Wasm
  c2wasm_start();
  
  // Expose the C function to JavaScript
  c2wasm_set_object_prop_function(c2wasm_window, "set_div_value", set_div_value);
}