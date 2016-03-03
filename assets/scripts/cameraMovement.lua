-- gameObject
-- speed

function Update(gameTimer)
	
	local dx = gameTimer.elapsedTimeSeconds * speed
	
	local pos = gameObject.transform.position
	local rot = gameObject.transform.rotation	
	
	if input:IsPressed(KEY.CONTROL) then
		if input:IsPressed(KEY.W) then
			rot.y = rot.y + dx
		end
		if input:IsPressed(KEY.S) then
			rot.y = rot.y - dx
		end
		if input:IsPressed(KEY.A) then
			rot.x = rot.x - dx
		end
		if input:IsPressed(KEY.D) then
			rot.x = rot.x + dx
		end
	else
		if input:IsPressed(KEY.W) then
			pos.x = pos.x - dx;
		end
		if input:IsPressed(KEY.S) then
			pos.x = pos.x + dx;
		end
		if input:IsPressed(KEY.A) then
			pos.z = pos.z - dx;
		end
		if input:IsPressed(KEY.D) then
			pos.z = pos.z + dx;
		end
	end
	
	gameObject.transform.position = pos
	gameObject.transform.rotation = rot
		
end