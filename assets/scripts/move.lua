------ Automatically ------
-- camera
-- gameObject

------- Script Specific ------


function Update(gameTimer)
	
	local pos = gameObject.transform.position
	
	if input:IsPressed(KEY.S) then
		pos.y = pos.y - 0.1
	end
	if input:IsPressed(KEY.W) then
		pos.y = pos.y + 0.1
	end
	
	gameObject.transform.position = pos
	
end