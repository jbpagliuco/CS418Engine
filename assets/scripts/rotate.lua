------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------
-- speed

function Update(gameTimer)
	
	local dr = gameTimer.elapsedTimeSeconds * speed
	
	local rot = gameObject.transform.rotation
	rot.y = rot.y + dr;	
	
	gameObject.transform.rotation = rot
		
end