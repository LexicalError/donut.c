# donut.c
IT'S A SPINNING DONUT

#calculations:
x = (R + rcos(theta))
y = (rsin(theta))
z = (0)

rotate around y:
-> (cos(phi)(R + rcos(theta)), rsin(theta), sin(phi)(R+rcos(theta)))

animate:
rotate around x & z by A and B:
-> 
x = cos(B)cos(phi)(R + rcos(theta)) + sin(B)[rcos(A)sin(theta) + sin(A)sin(phi)(R + rcos(theta))]
y = cos(B)[rcos(A)sin(theta) + sin(A)sin(phi)(R+rcos(theta))] - sin(B)cos(phi)(R+rcos(theta))
z = cos(A)sin(phi)(R+rcos(theta))-rsin(A)sin(theta)

normal vectors:
(cos(theta), sin(theta), 0)
rotate with phi, A, B:
->
x = cos(B)cos(theta)cos(phi) + sin(B)[cos(A)sin(theta) + sin(A)cos(theta)sin(phi)]
y = cos(B)[cos(A)sin(theta) + sin(A)cos(theta)sin(phi)] - sin(B)cos(theta)cos(phi)
z = cos(A)cos(theta)sin(phi) - sin(A)sin(theta)
light direction:
(1, 0, -1)
-> luminace value:
cos(B)cos(theta)cos(phi) + sin(B)cos(A)sin(theta) + sin(B)sin(A)cos(theta)sin(phi) - cos(A)cos(theta)sin(phi) + sin(A)sin(theta)
