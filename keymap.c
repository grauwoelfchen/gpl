#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

#include "keymap_extras/keymap_dvorak.h"

extern keymap_config_t keymap_config;


#define _DVORAK 0
#define _LOWER  1
#define _RAISE  2

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0 (Dvorak)
 * ,-----------------------------------------------------------------------------------.
 * |   "  |   ,  |   .  |   P  |   Y  |      |      |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  |      |      |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  |      | Rais |   B  |   M  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   _  |      | Shft | Bksp | Ctrl | Alt  | Spce | Lowr |      |   /  | Entr |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    _______, _______, DV_F,    DV_G,    DV_C,    DV_R,    DV_L  },
  {DV_A,    DV_O,    DV_E,    DV_U,    DV_I,    _______, _______, DV_D,    DV_H,    DV_T,    DV_N,    DV_S  },
  {DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    _______, RAISE,   DV_B,    DV_M,    DV_W,    DV_V,    DV_Z  },
  {KC_ESC,  DV_MINS, _______, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  LOWER,   _______, DV_SLSH, KC_ENT}
},

/* Layer 1 (Lower)
 * ,-----------------------------------------------------------------------------------.
 * |   !  |   @  |   {  |   }  |   |  |      |      | Pgup |   7  |   8  |   9  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   #  |   $  |   (  |   )  |   `  |      |      | Pgdn |   4  |   5  |   6  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   %  |   ^  |   [  |   ]  |   ~  |      |      |   &  |   1  |   2  |   3  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  Tab |      |      |      | Ctrl | Alt  |      |      |      |   0  |  =   |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {DV_EXLM, DV_AT,   DV_LCBR, DV_RCBR, KC_PIPE, _______, _______, KC_PGUP, DV_7,    DV_8,    DV_9,    DV_ASTR},
  {DV_HASH, DV_DLR,  DV_LPRN, DV_RPRN, DV_GRV,  _______, _______, KC_PGDN, DV_4,    DV_5,    DV_6,    DV_PLUS},
  {DV_PERC, DV_CIRC, DV_LBRC, DV_RBRC, DV_TILD, _______, _______, DV_AMPR, DV_1,    DV_2,    DV_3,    KC_BSLS},
  {KC_ESC,  KC_TAB,  _______, _______, _______, KC_LCTL, KC_LALT, _______, _______, _______, DV_0,    DV_EQL }
},

/* Layer 2 (Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  ↑   |      |      |      |      |      |  F7  |  F8  |  F9  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  ←   |  ↓   |   →  |      |      |      |      |  F4  |  F5  |  F6  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | Rest |      |      |  F1  |  F2  |  F3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Ctrl | Alt  |      |      |      |  F0  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_FN7,  KC_FN8,  KC_FN9,  _______},
  {_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_FN4,  KC_FN5,  KC_FN6,  _______},
  {_______, _______, _______, _______, _______, RESET,   _______, _______, KC_FN1,  KC_FN2,  KC_FN3,  _______},
  {_______, _______, _______, _______, _______, KC_LCTL, KC_LALT, _______, _______, _______, KC_FN0,  _______}
},
};

const uint16_t PROGMEM fn_actions[] = {

};

#ifdef AUDIO_ENABLE

float tone_startup[][2] = SONG(STARTUP_SOUND);
float tone_dvorak[][2]  = SONG(DVORAK_SOUND);
float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      break;
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      break;
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      break;
      return false;
  }
  return true;
};

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20);
  PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
