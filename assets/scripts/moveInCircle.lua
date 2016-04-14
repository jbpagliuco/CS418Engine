------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------
-- speed
-- radius

dir = 0.0

function Update(gameTimer)
	
	dir = 0.0
	if input:IsPressed(KEY.LEFT) then
		dir = -1.0
	end
	if input:IsPressed(KEY.RIGHT) then
		dir = 1.0
	end
	if input:IsPressed(KEY.UP) then
		radius = radius - 0.1
	end
	if input:IsPressed(KEY.DOWN) then
		radius = radius + 0.1
	end
	
	theta = theta + gameTimer.elapsedTimeSeconds * dir
	
	local pos = Vector3f(0.0, 0.5, 0.0)
	pos.x = radius * math.cos(theta)
	pos.z = radius * math.sin(theta)
	
	local target = Vector3f(0.0, 0.0, 0.0)
	local up = Vector3f(0.0, 1.0, 0.0)
	camera:SetViewMatrix(Vector.FromVector3f(pos), Vector.FromVector3f(target), Vector.FromVector3f(up))
	
	print(pos.x, ", ", pos.y, ", ", pos.z);
	
end