------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------
-- speed

function Update(gameTimer)
	
	local dr = gameTimer.elapsedTimeSeconds * speed
	
	local rot = gameObject.transform.rotation
	
	if input:IsPressed(KEY.SPACE) then
		rot.y = rot.y + dr;	
	end
	
	local pos = gameObject.transform.position
	
	if input:IsPressed(KEY.Q) then
		pos.y = pos.y - 0.1
	end
	if input:IsPressed(KEY.E) then
		pos.y = pos.y + 0.1
	end
	
	gameObject.transform.position = pos
	
	gameObject.transform.rotation = rot
		
end