# Mortar
Mortar, an outstanding project by Fab

Context: You are working on a prototype of a 2D tower defense game for
a mobile platform, using approximated physics. The basic
systems that drive the game are to be developed independently
of the later graphics system ( which is not ready yet :| )


a. Write a small console application that contains a simple game loop
and uses screen-space coordinates.
b. Using different console symbols (perhaps from the 'charmap'),
colors and sfx implement the objects and features as outlined in
the images in the realm of an infinite play mode:
i. a mortar emplacement with 2 or more defensive walls


ii. 2x mortars (or grenade launchers)

iii. 4x types of shells (or grenades)
S           R       BR       DD       LT
1 (light)   far     small    light    fast
2 (medium)  medium  medium   medium   medium
3 (heavy)   near    large    heavy    slow
4 (incendiary) medium small light(continuous over 3 frames) slow


Note: the damage dealt by a detonation decreases linearily from the point
of impact outward in a circular fashion throughout the blast radius.
