// Title: ISO/DIN standard Screw Holes
// Author: Carlo Wood
// Date: 26/8/2016
// License: Creative Commons - Share Alike - Attribution

// Description: Screw holes come in many forms and sizes and are
// a recurring necessity. This library intends to provide an
// easy way to add holes to your projects for screws.

// Usage:
//
// include <screw_holes.scad>
// screw_hole_fn = 64;                // Optional. The default is 32.
//
// difference()
// {
//   draw_solid_object();
//   translate(screw_position)
//     rotate(screw_orientation)
//       screw_hole(iso_norm, metric, length, thread_length, fn);
// }
//
// For example,
//       screw_hole(DIN34811, M3, 20);
// or
//       screw_hole([8.4, 2.7, 90], M4, 20); // dk = 8.4, k = 2.7, a = 90.
//
// The default fn is set to the global 'screw_hole_fn', which can be optionally
// be changed after including screw_holes.scad.
//
// The default thread_length is 0, causing the length to be extended
// with screw_hole_length_extend (0.1 mm) to make sure we get through
// the solid object.
//
// The length INCLUDES the head height, even for cylinder-head screws,
// when the screw is to be sunken (the default).
//
//          ^         ___  ________
//          |        |   |       ^   ^
//          |        |   |       |   |-- thread_length - screw_hole_length_extend
//          |     *) /   \       | __v_
//         -+- - - -|     |--  --|--\_ screw_hole_length_extend
//          ^       |     |      |
//   solid  |       |     |      |-- length                      ^
//   object |       |     |      |                               | z-axis
//          |    ,--'     '--. --|--                             |
//         _v____|___________| __v__`head height (k)             |____ xy plane
//               '-----|-----' ----\_ screw_hole_height_extend
//                     |__ Center position of screw hole (origin)
//
// The origin of the screw hole is to be positioned onto the surface of the solid object.
// *) In the case that there is a narrower cylinder for the thread of the screw
// to be screwed into, the diameter of the shaft is reduced with a cone of 90 degrees
// in order to make it printable with the head at the bottom.
//

// Global variables.
screw_hole_fn = 32;                      // Number of segments for a full circle.
screw_hole_length_extend = 0.1;          // Extra length of the non-threaded part of the screw hole.
screw_hole_height_extend = 0.1;          // Extra distance the hole extends above the surface.
screw_hole_cylinderhead_spacing = 0.1;   // Extra radius of hole around screw head.
screw_hole_countersunk_delta = 0.2;      // Extra depth of countersunk screw hole.

// Metric index.
M1_6 = 0;
M2   = 1;
M2_5 = 2;
M3   = 3;
M3_5 = 4;
M4   = 5;
M5   = 6;
M6   = 7;
M8   = 8;
M10  = 9;

// ISO and DIN index.
// Cylinder head screws.
ISO4762 = 0; DIN912 = 0;        // Hexagon socket head cap screws.

// Metric countersunk screws.
screw_hole_begin_countersunk = 1;
DIN963 = 1;                     // Slotted countersunk head screws.
DIN965 = 1;                     // Cross-recessed countersunk flat head screws.
DIN34811 = 2;                   // Cross-recessed countersunk flat head plastic screws.
ISO2009 = 3;                    // Slotted countersunk flat head screws.
ISO7046 = 3;			// Cross-recessed countersunk flat head screws.
ISO14581 = 3;                   // Hexalobular socket countersunk head screws, nominal dk values.
ISO14581m = 4;                  // Hexalobular socket countersunk head screws, maximum dk values.
ISO10642 = 5;                   // Hexagon socket countersunk head screws.

///////////////////////////////////////////////////////////////////////////////
// Test case
/*
include <screw_holes.scad>

difference()
{
  %translate([-10, -10, 0])
    cube([20, 20, 20]);
}

// Drill a hole for a DIN965 M3 screw with 20 mm long, and 10 mm thread.
color("yellow")
  screw_hole(DIN965, M3, 20, 10);
*/
///////////////////////////////////////////////////////////////////////////////

// These values are just a random guess for now.
screw_hole_thread_depth = [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
     0.08,  0.1,  0.125, 0.15,  0.175,  0.2,  0.25,   0.3,   0.4,   0.5
];

// Outer diameter of thread.
screw_hole_d = [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
     1.6,   2,     2.5,   3,     3.5,   4,     5,     6,     8,     10
];

// dk : The max. outer diameter of screw head (the min. is a few tenth less).
// k  : The (max) height of the screw head.

// With thanks to http://www.globalfastener.com/ for making these values available to the public.
screw_standard = [

  // ISO 4762 / DIN 912
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [ 3.0,   3.8,   4.5,   5.5,   6.0,   7.0,   8.5,  10.0,  13.0,  16.0 ], // dk
   [ 1.6,   2.0,   2.5,   3.0,   3.5,   4.0,   5.0,   6.0,   8.0,  10.0 ]  // k
  ],

  // DIN 963 / DIN 965
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [ 3.0,   3.8,   4.7,   5.6,   6.5,   7.5,   9.2,  11.0,  14.5,  18.0 ], // dk
   [ 0.96,  1.2,   1.5,   1.65,  1.93,  2.2,   2.5,   3.0,   4.0,   5.0 ]  // k
  ],

  // DIN 34811
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [-1,    -1,    -1,     5.5,  -1,     8.4,   9.3,  11.3,  15.8,  -1 ],  // dk
   [-1,    -1,    -1,     1.65, -1,     2.7,   2.7,   3.3,   4.65, -1 ]   // k
  ],

  // ISO 2009 / ISO 7046 / ISO 14581 (nominal dk values)
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [ 3.0,   3.8,   4.7,   5.5,   7.3,   8.4,   9.3,  11.3,  15.8,  18.3 ], // dk
   [ 1.0,   1.2,   1.5,   1.65,  2.35,  2.7,   2.7,   3.3,   4.65,  5.0 ]  // k
  ],

  // ISO 14581 (max dk values)
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [-1,     4.4,   5.5,   6.3,   8.2,   9.4,  10.5,  12.6,  17.3,  20.0 ], // dk
   [-1,     1.2,   1.5,   1.65,  2.35,  2.7,   2.7,   3.3,   4.65,  5.0 ]  // k
  ],

  // ISO 10642 (max dk values)
  [
  // M1_6   M2     M2_5   M3     M3_5   M4     M5     M6     M8     M10
   [-1,    -1,    -1,     6.72, -1,     8.96, 11.20, 13.44, 17.92, 22.40 ], // dk
   [-1,    -1,    -1,     1.86, -1,     2.48,  3.10,  3.72,  4.96,  6.20 ]  // k
  ],
];

// Index for screw parameters.
screw_hole_dk = 0;
screw_hole_k = 1;
screw_hole_a = 2;

// Draw a hole of fn segments that fits around a cylinder with radius.
module sh_cylinder_outer(height, radius, fn)
{
  fudge = 1 / cos(180 / fn);
  cylinder(h = height, r = radius * fudge, $fn = fn);
}

// Draw a cone of height, in fn segments, that at its top fits around a cylinder with radius.
module sh_cone_outer(height, radius, fn)
{
  fudge = 1 / cos(180 / fn);
  translate([0, 0, height / 2])
    cylinder(height, radius * fudge, 0, true, $fn = fn);
}

// The main module.
//
// iso: One of the global ISO* or DIN* constants defined above.
//      Or a two dimensional vector [dk, k] or a three dimensional vector [dk, k, a], where
//      dk: the diameter of the head of the screw.
//      k : the height of the head of the screw.
//      a : the angle of conic part of the countersunk head of the screw.
// m  : One of the global M* constants defined above.
// L  : The thickness of the object that the hole to go through (b must be zero),
//      or the depth of the hole (b should be larger than zero).
// b  : The length of the hole that needs to be narrower than the m value
//      for the purpose of tapping a screw thread into (or you might try to use
//      a self-tapping screw).
// fn : facet number.
// ext: Hole extension ABOVE the screw head (with the same width as the head).

module screw_hole(iso, m, L, b = 0, fn = screw_hole_fn, ext = 0)
{
  d = screw_hole_d[m];
  dk = (len(iso) > 1) ? iso[screw_hole_dk] : screw_standard[iso][screw_hole_dk][m];
  k = (len(iso) > 1) ? iso[screw_hole_k] :  screw_standard[iso][screw_hole_k][m];
  a = (len(iso) > 1) ? ((len(iso) == 2) ? 180 : iso[screw_hole_a])
                     : iso >= screw_hole_begin_countersunk ? 90 : 180;
  s = d - 2 * screw_hole_thread_depth[m];
  l = L - b;

  union()
  {
    // The thread.
    if (b > 0)
    {
      translate([0, 0, l])
	sh_cylinder_outer(b, s / 2, fn);
    }

    // Extend hole above screw head.
    if (ext > 0)
    {
      translate([0, 0, -ext])
	sh_cylinder_outer(ext, dk / 2, fn);
    }

    // The non-thread.
    sh_cylinder_outer(l + screw_hole_length_extend, d / 2, fn);

    // The transistion from non-thread to thread.
    if (b > 0)
    {
      intersection()
      {
	sh_cylinder_outer(l + b, d / 2, fn);
	// The transition between non-thread and thread:
	//    screw_hole_thread_depth[m]
	//           \
	//           . |   s   | .
	//           . |<----->| .   | b
	//           . |       | .   |
	// cone -->  ./_________\.  _v_
	//        _ /|___________|\ ___ -- screw_hole_length_extend
	//       /   |<--------->|.  ^
	// cone base |     d   h |.  | l
	//                  ------>
	//                   
	// The cone base must be d where it hits the non-thread part,
	// but we generate an overlap so that the cone base that
        // we need to draw is d + 2 * screw_hole_length_extend.
	// The height is therefore d / 2 + screw_hole_length_extend.
	h = d / 2 + screw_hole_length_extend;
	translate([0, 0, l])
	  sh_cone_outer(h, h, fn);
      }
    }

    // The head.
    //
    // Note that dk is increased with 2 * screw_hole_cylinderhead_spacing,
    // and k is increased with screw_hole_countersunk_delta if a < 180.
    if (a < 180)
    {
      // The dimensions of a countersunk head:
      //                     d
      //                   <--->
      //                  |  .  |    ____                             ___
      //                  | /a\ |      ^-- pk                          ^
      //    solid  |      |     |    __v_                              |
      //    object |     /       \     ^                               |ch
      //           |    /         \    |-- k                           |
      //          _v___|___________| __v__                             v
      //              /'-----------'\----\_ screw_hole_height_extend  ---
      //                <---dk----> 
      //              <-----cb------>
      // 
      // pk : distance to peak of cone.
      // ch : total cone height.
      // cb : cone base.

      tt = 2 * tan(a / 2);	// Ratio between base and height of cone.
      pk = d / tt;
      ch = pk + (k + screw_hole_countersunk_delta) + screw_hole_height_extend;
      cb = ch * tt;

      if (cb < dk)
        echo("WARNING: screw_hole(): inconsistent values in first parameter", iso);

      translate([0, 0, -screw_hole_height_extend])
	intersection()
	{
	  sh_cone_outer(ch, cb / 2, fn);
	  cylinder(ch, r = dk / 2 + screw_hole_cylinderhead_spacing, $fn = fn);
	}
    }
    else
    {
      translate([0, 0, -screw_hole_height_extend])
	sh_cylinder_outer(screw_hole_height_extend + k, dk / 2 + screw_hole_cylinderhead_spacing, fn);
    }
  }
}
