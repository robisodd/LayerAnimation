/* ------------------------------------------------------------------------ //
//  Notes
// ------------------------------------------------------------------------ //

#define FONT_KEY_FONT_FALLBACK "RESOURCE_ID_FONT_FALLBACK"
#define FONT_KEY_GOTHIC_14 "RESOURCE_ID_GOTHIC_14"
#define FONT_KEY_GOTHIC_14_BOLD "RESOURCE_ID_GOTHIC_14_BOLD"
#define FONT_KEY_GOTHIC_18 "RESOURCE_ID_GOTHIC_18"
#define FONT_KEY_GOTHIC_18_BOLD "RESOURCE_ID_GOTHIC_18_BOLD"
#define FONT_KEY_GOTHIC_24 "RESOURCE_ID_GOTHIC_24"
#define FONT_KEY_GOTHIC_24_BOLD "RESOURCE_ID_GOTHIC_24_BOLD"
#define FONT_KEY_GOTHIC_28 "RESOURCE_ID_GOTHIC_28"
#define FONT_KEY_GOTHIC_28_BOLD "RESOURCE_ID_GOTHIC_28_BOLD"
#define FONT_KEY_BITHAM_30_BLACK "RESOURCE_ID_BITHAM_30_BLACK"
#define FONT_KEY_BITHAM_42_BOLD "RESOURCE_ID_BITHAM_42_BOLD"
#define FONT_KEY_BITHAM_42_LIGHT "RESOURCE_ID_BITHAM_42_LIGHT"
#define FONT_KEY_BITHAM_42_MEDIUM_NUMBERS "RESOURCE_ID_BITHAM_42_MEDIUM_NUMBERS"
#define FONT_KEY_BITHAM_34_MEDIUM_NUMBERS "RESOURCE_ID_BITHAM_34_MEDIUM_NUMBERS"
#define FONT_KEY_BITHAM_34_LIGHT_SUBSET "RESOURCE_ID_BITHAM_34_LIGHT_SUBSET"
#define FONT_KEY_BITHAM_18_LIGHT_SUBSET "RESOURCE_ID_BITHAM_18_LIGHT_SUBSET"
#define FONT_KEY_ROBOTO_CONDENSED_21 "RESOURCE_ID_ROBOTO_CONDENSED_21"
#define FONT_KEY_ROBOTO_BOLD_SUBSET_49 "RESOURCE_ID_ROBOTO_BOLD_SUBSET_49"
#define FONT_KEY_DROID_SERIF_28_BOLD "RESOURCE_ID_DROID_SERIF_28_BOLD"


Different layer animation types:
------------------------------------
  Switch between layers: (no difference between 2 or many)
    (An array of pointers for order of layers)
    [FB]=FrameBuffer: Achieved by drawing 1st layer, reading framebuffer, altering framebuffer, drawing 2nd layer
                  Needs to interject it's drawing function between the 2 layers
    Fill with color:
      Fill with [color] then next layer
      Dissolve
        Size of dots or squares
        Random or gridlike
      Drip current layer down

  2D
      Swipe left/right/up/down
      Shuffle (like a deck of cards)
        Shuffle direction (over top, underneath)
      [FB] Shrink, fling away
      
    3D
      
      Rotate around
      flip vertically
        For(amount=1,amount<10,amount++) Shrink(Layer1,amount)
        
------------------------------------
  Popups
    Pop up from bottom
    Swing in from side/top/bottom
    Swing out from other direction


Notes:
  Switch: 
  Layers need to all be same size and position
  Popup:  layer duration, speed, position, animation method

------------------------------------ */