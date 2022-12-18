#include <stdio.h>
#include <stdint.h>
#include "auddev.h"

int num_sessions = 0;

int main() {
  /* startup */
  audio_init_interfaces();

  {
    uint32_t const num_devices = audio_get_device_count();
    uint32_t i;
    printf("Found %d audio devices%s\n", num_devices, num_devices > 0 ? ":" : ".");
    for (i = 0; i < num_devices; i++) {
      audio_device_details_t const *device_info = audio_get_device_details(i);
      if (device_info) {
        printf("\t%d: %s\n", i, device_info->name);
      }
    }
  }

  /* shutdown */
  audio_free_interfaces();
  return 0;
}
