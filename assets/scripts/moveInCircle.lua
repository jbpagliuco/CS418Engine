------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------
-- speed
-- radius

function Update(gameTimer)
	
	local dr = speed * gameTimer.playingTime
	
	local pos = Vector3f(0.0, 0.5, 0.0)
	pos.x = radius * math.cos(dr)
	pos.z = radius * math.sin(dr)
	
	local target = Vector3f(0.0, 0.0, 0.0)
	local up = Vector3f(0.0, 1.0, 0.0)
	camera:SetViewMatrix(Vector.FromVector3f(pos), Vector.FromVector3f(target), Vector.FromVector3f(up))
	
	
	if input:IsPressed(KEY.LEFT) then
		speed = speed - 0.000001
	end
	if input:IsPressed(KEY.RIGHT) then
		speed = speed + 0.000001
	end
	if input:IsPressed(KEY.UP) then
		radius = radius - 0.1
	end
	if input:IsPressed(KEY.DOWN) then
		radius = radius + 0.1
	end
	
end