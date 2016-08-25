
global wheelPositions wheelSizes;
wheelPositions = [0, 0; 0, -10; 0, 10];
wheelSizes = [15, 11, 11, 11, 11, 11];


function l = lengthAroundWheel(wheelNum, angle)
  global wheelSizes;
  l = wheelSizes(wheelNum) * angle;
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
 endfunction

[d, a] = lineDetails(3, 2)
angleOfLine(3, 2)