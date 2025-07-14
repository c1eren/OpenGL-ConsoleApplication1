// point light [3]
lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
lightingShader.setVec3("pointLights[3].ambient", pAmbient);
lightingShader.setVec3("pointLights[3].diffuse", pDiffuse);
lightingShader.setVec3("pointLights[3].specular", pSpecular);
lightingShader.setFloat("pointLights[3].constant", attConstant);
lightingShader.setFloat("pointLights[3].linear", attLinear);
lightingShader.setFloat("pointLights[3].quadratic", attQuadratic);
