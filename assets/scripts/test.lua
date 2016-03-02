-- gameObject
-- speed

function Update(gameTimer)
	
	local v;
	local q1 = Quaternion(0.0, 1.0, 0.0, speed * gameTimer.elapsedTimeSeconds)
	local q2 = Quaternion(0.0, 1.0, 0.0, speed * -gameTimer.elapsedTimeSeconds)
	
	if input:IsPressed(KEY.A) then
		v = gameObject.transform.rotation
		v = q1:MultiplyQuaternion(v);
		gameObject.transform.rotation = v
	end
	if input:IsPressed(KEY.D) then
		v = gameObject.transform.rotation
		v = q2:MultiplyQuaternion(v);
		gameObject.transform.rotation = v
	end
		
end