-- gameObject
-- speed

function Update(gameTimer)
	
	local qLookUp = Quaternion(1.0, 0.0, 0.0, speed * -gameTimer.elapsedTimeSeconds)
	local qLookDown = Quaternion(1.0, 0.0, 0.0, speed * gameTimer.elapsedTimeSeconds)
	local qLookRight = Quaternion(0.0, 1.0, 0.0, speed * -gameTimer.elapsedTimeSeconds)
	local qLookLeft = Quaternion(0.0, 1.0, 0.0, speed * gameTimer.elapsedTimeSeconds)
	
	local v = gameObject.transform.rotation
	
	if input:IsPressed(KEY.W) then
		v = qLookUp:MultiplyQuaternion(v);
	end
	if input:IsPressed(KEY.S) then
		v = qLookDown:MultiplyQuaternion(v);	
	end
	if input:IsPressed(KEY.A) then
		v = qLookLeft:MultiplyQuaternion(v);
	end
	if input:IsPressed(KEY.D) then
		v = qLookRight:MultiplyQuaternion(v);	
	end
	
	gameObject.transform.rotation = v
		
end