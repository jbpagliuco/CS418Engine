Update = function()

	local v = Vector3f()
	v = gameObject.transform.rotation
	v.y = v.y + gameTimer.totalGameTime

	gameObject.transform.rotation = v

	print("Worked")
	
end