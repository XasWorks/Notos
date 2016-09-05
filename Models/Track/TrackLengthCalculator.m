
global wheelPositions wheelSizes;

wheelPositions = [[0, 40]
						[-57, 35]
						[-45, 10]
						[-15, 10]
						[15, 10]
						[45, 10]];
wheelSizes = [15, 10, 10, 10, 10, 10];

function l = lengthAroundWheel(wheelNum, angle)
  global wheelSizes;
  l = abs(wheelSizes(wheelNum) * angle);
endfunction

function [d, a] = lineDetails(wheelA, wheelB)
  global wheelPositions wheelSizes;
  
  conVect = wheelPositions(wheelB,:) - wheelPositions(wheelA,:);
  initAngle = atan2(conVect(1), conVect(2));

  l = norm(conVect);
  rDiff = wheelSizes(wheelB) - wheelSizes(wheelA);

  extrAngle = asin(rDiff / l);

  a = initAngle - extrAngle;
  d = l * cos(extrAngle);
  
    printf("Calculated the details for wheels %i to %i!\n Wheel-Wheel angle: %f - distance: %f\n Tanget angle: %f - length: %f\n\n", wheelA, wheelB, initAngle, l, a, d);
endfunction

function i = arLoop(n)
  global wheelSizes;
  i = mod(n - 1, length(wheelSizes)) + 1;
endfunction


totalDistance = 0;
lastAngle = 0;

[null, lastAngle] = lineDetails(length(wheelSizes), 1);

for i=(1:length(wheelSizes))
  [d, a] = lineDetails(arLoop(i), arLoop(i+1));
  totalDistance = totalDistance + d + lengthAroundWheel(i, lastAngle - a);

  lastAngle = a;
endfor

totalDistance
suggestedRadius = totalDistance / (2*pi)
