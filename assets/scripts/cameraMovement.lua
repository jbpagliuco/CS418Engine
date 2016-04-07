------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------
-- speed
-- rotationSpeed

function Update(gameTimer)
	
	local dx = gameTimer.elapsedTimeSeconds * speed
	local dr = gameTimer.elapsedTimeSeconds * rotationSpeed
	
	local vPos = Vector.FromVector3f(gameObject.transform.position)
	local rot = gameObject.transform.rotation
	
	vPos = vPos:Add(camera.forward:MultiplyScalar(dx))
	
	if input:IsPressed(KEY.W) then
		speed = speed + 0.1
	end
	if input:IsPressed(KEY.S) then
		speed = speed - 0.1
	end
	
	if input:IsPressed(KEY.LEFT) then
		rot.z = rot.z - dr
	end
	if input:IsPressed(KEY.RIGHT) then
		rot.z = rot.z + dr
	end
	gameObject.transform.rotation = rot
	
	
	
	
	local qRot = Quaternion.FromEuler(gameObject.transform.rotation.x, gameObject.transform.rotation.y, gameObject.transform.rotation.z)
	
	if input:IsPressed(KEY.UP) then
		local q = Quaternion(1.0, 0.0, 0.0, -dr)
		qRot = q:MultiplyQuaternion(qRot)
	end
	if input:IsPressed(KEY.DOWN) then
		local q = Quaternion(1.0, 0.0, 0.0, dr)
		qRot = q:MultiplyQuaternion(qRot)
	end
	gameObject.transform.rotation = qRot:ToEuler()
	
	
	gameObject.transform.position = vPos:ToVector3f()
		
end