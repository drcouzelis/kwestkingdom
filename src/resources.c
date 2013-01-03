#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "resources.h"
#include "utilities.h"


#define MAX_RESOURCES 256
#define MAX_RESOURCE_PATHS 4
#define MAX_FILENAME_LEN 256

#define GAME_VOLUME 192


typedef enum
{
  RESOURCE_TYPE_IMAGE = 0,
  RESOURCE_TYPE_SOUND,
  RESOURCE_TYPE_MUSIC
} RESOURCE_TYPE;


typedef struct
{
  char name[MAX_FILENAME_LEN];
  RESOURCE_TYPE type;
  void *data;
} RESOURCE;


static RESOURCE *resources[MAX_RESOURCES];
static int num_resources = 0;

static char resource_paths[MAX_RESOURCE_PATHS][MAX_FILENAME_LEN];
static int num_resource_paths = 0;

static FLAG sound_enabled = ON;


void init_resources()
{
  int i;

  for (i = 0; i < MAX_RESOURCES; i++) {
    resources[i] = NULL;
  }

  set_volume(GAME_VOLUME, GAME_VOLUME);
}


void stop_resources()
{
  int i;

  for (i = 0; i < num_resources; i++) {
    if (resources[i]) {
      if (resources[i]->type == RESOURCE_TYPE_IMAGE) {
        destroy_bitmap((IMAGE *)resources[i]->data);
      } else if (resources[i]->type == RESOURCE_TYPE_SOUND) {
        destroy_sample((SOUND *)resources[i]->data);
      }
      free_memory("RESOURCE", resources[i]);
      resources[i] = NULL;
    }
  }

  num_resources = 0;
}


void add_resource_path(const char *path)
{
  if (num_resource_paths >= MAX_RESOURCE_PATHS) {
    fprintf(stderr, "RESOURCES: Failed to add path.\n");
    fprintf(stderr, "RESOURCES: Try increasing MAX_RESOURCE_PATHS.\n");
    return;
  }

  /**
   * Add the new path to the list of resource paths.
   */
  strncpy(resource_paths[num_resource_paths], path, MAX_FILENAME_LEN - 1);

  num_resource_paths++;
}


/**
 * Load a bitmap and set magic pink to transparent.
 */
IMAGE *load_bitmap_with_magic_pink(const char *filename)
{
  IMAGE *bitmap;
  static PALETTE palette;

  bitmap = load_bitmap(filename, palette);

  /*
  if (bitmap) {
    al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 255));
  }
  */

  return bitmap;
}


/**
 * Create a RESOURCE structure.
 */
RESOURCE *create_resource(const char *name, RESOURCE_TYPE type, void *data)
{
  RESOURCE *resource;

  resource = alloc_memory("RESOURCE", sizeof(RESOURCE));
  if (resource) {
    strncpy(resource->name, name, MAX_FILENAME_LEN - 1);
    resource->type = type;
    resource->data = data;
  }

  return resource;
}


void *get_resource(const char *name, RESOURCE_TYPE type)
{
  void *data = NULL;
  char fullpath[MAX_FILENAME_LEN];
  int i;

  /**
   * Check the loaded resource
   */
  for (i = 0; i < num_resources; i++) {
    if (resources[i] == NULL) {
      printf("Resource %d is NULL\n", i);
    }
    if (strncmp(resources[i]->name, name, MAX_FILENAME_LEN) == 0) {
      return resources[i]->data;
    }
  }

  if (num_resources == MAX_RESOURCES) {
    fprintf(stderr, "RESOURCES: Failed to load resource.\n");
    fprintf(stderr, "RESOURCES: Try increasing MAX_RESOURCES.\n");
    return NULL;
  }

  /**
   * Try finding it in the list of resource paths.
   */
  for (i = 0; i < num_resource_paths; i++) {

    fullpath[0] = '\0';
    strncat(fullpath, resource_paths[i], MAX_FILENAME_LEN);
    strncat(fullpath, name, MAX_FILENAME_LEN);

    if (type == RESOURCE_TYPE_IMAGE) {
      data = load_bitmap_with_magic_pink(fullpath);
    } else if (type == RESOURCE_TYPE_SOUND) {
      data = load_sample(fullpath);
    }

    if (data) {
      resources[num_resources] = create_resource(name, type, data);
      num_resources++;
      return data;
    }
  }

  fprintf(stderr, "RESOURCES: Failed to load resource: \"%s\".\n", name);
  return NULL;
}


IMAGE *get_image(const char *name)
{
  return (IMAGE *)get_resource(name, RESOURCE_TYPE_IMAGE);
}


SOUND *get_sound(const char *name)
{
  return (SOUND *)get_resource(name, RESOURCE_TYPE_SOUND);
}


void play_sound(SOUND *sound)
{
  if (sound_enabled && sound) {
    play_sample(sound, 255, 128, 1000, 0);
  }
}


void toggle_sound(void)
{
  sound_enabled = !sound_enabled;
}


FLAG is_sound_enabled()
{
  return sound_enabled;
}

