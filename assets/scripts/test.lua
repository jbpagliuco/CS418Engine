function Update(gameTimer)

	local v = Vector3f()
	v = gameObject.transform.rotation
	
	v.y = v.y + gameTimer.elapsedTimeSeconds

	gameObject.transform.rotation = v
	
	if gameObject.transform.rotation.y > math.pi then
		gameObject:GetScriptComponents("ScriptComponent")[1].enabled = false
	end
	
end