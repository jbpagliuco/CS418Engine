------ Automatically ------
-- camera
-- gameObject
-- scene

------- Script Specific ------

intensitySmoothing = 0.1

function Update(gameTimer)
	
	local lightComp = gameObject:GetLightComponents("LightComponent")[1];
	local light = lightComp.light
	
	local dir = light.direction
	dir.y = dir.y + gameTimer.elapsedTimeSeconds
	light.direction = dir
	
	if light.direction.y > 0 then
		light.intensity = light.intensity - gameTimer.elapsedTimeSeconds * intensitySmoothing
	end
	
	if light.intensity < 0 then
		local scriptComp = gameObject:GetScriptComponents("ScriptComponent")[1];
		scriptComp.enabled = false
	end
	
	lightComp.light = light
	
end