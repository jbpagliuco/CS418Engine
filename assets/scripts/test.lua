function Update(gameTimer)

	local v = Vector3f()
	v = gameObject.transform.rotation
	
	v.y = v.y + gameTimer.elapsedTimeSeconds

	gameObject.transform.rotation = v
	
end