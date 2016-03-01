
function Update(gameTimer)
	
	local v;
	
	if input:IsPressed(KEY.A) then
		v = gameObject.transform.rotation
		v.y = v.y + speed * gameTimer.elapsedTimeSeconds
		gameObject.transform.rotation = v
	end
	
	print(name)
		
end