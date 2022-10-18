

var container;
var camera, scene, renderer;
var mouseX = 0,
    mouseY = 0;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;

// Object3D ("Group") nodes and Mesh nodes
var sceneRoot = new THREE.Group();
//Earth
var earthOrbit = new THREE.Group();
var earthSpin = new THREE.Group();
var earthTilt = new THREE.Group();
var earthTransl = new THREE.Group();
var earthScale = new THREE.Group();
var earthMesh;

//Moon
var moonOrbit = new THREE.Group();
var moonTransl = new THREE.Group();
var moonScale = new THREE.Group();
var moonMesh;

//Sun
var sunSpin = new THREE.Group();
var sunScale = new THREE.Group();
var sunMesh;

//Mars
var marsTransl = new THREE.Group();
var marsOrbit = new THREE.Group();
var marsSpin = new THREE.Group();

var animation = true;

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function onDocumentMouseMove(event) {
    // mouseX, mouseY are in the range [-1, 1]
    mouseX = (event.clientX - windowHalfX) / windowHalfX;
    mouseY = (event.clientY - windowHalfY) / windowHalfY;
}

function createSceneGraph() {
    scene = new THREE.Scene();

    const light = new THREE.PointLight( 0xffffff, 1.5, 50 );
    light.position.set( 0, 0, 0 );

    const ambientLight = new THREE.AmbientLight( 0x202020, 1.5); // soft white light
    
    // Top-level node
    scene.add(sceneRoot);
    // earth branch
    sceneRoot.add(ambientLight);
    ambientLight.add(earthTilt)
    earthTilt.add(earthScale);
    earthScale.add(earthOrbit);
    earthOrbit.add(earthTransl);
    earthTransl.add(earthSpin);
    earthSpin.add(earthMesh);

    //Moon branch
    earthMesh.add(moonScale);
    moonScale.add(moonOrbit);
    moonOrbit.add(moonTransl);
    moonTransl.add(moonMesh);

    //Sun branch
    sceneRoot.add(light);
    light.add( sunScale );
    sunScale.add(sunSpin);
    sunSpin.add(sunMesh);

    //Mars Branch
    sceneRoot.add(ambientLight);
    ambientLight.add(marsOrbit);
    marsOrbit.add(marsTransl);
    marsTransl.add(marsSpin);
    marsSpin.add(marsMesh);
    
}

function init() {
    container = document.getElementById('container');

    camera = new THREE.PerspectiveCamera(38, window.innerWidth / window.innerHeight, 0.1, 100);
    camera.position.z = 5;
    
    var texloader = new THREE.TextureLoader();
    
    // Earth mesh
	var geometryEarth = new THREE.SphereGeometry(0.8,32, 32);    

    var materialEarth = new THREE.MeshLambertMaterial();
    materialEarth.combine = 0;
    materialEarth.needsUpdate = true;
    materialEarth.wireframe = false; 
    
	const earthTexture = texloader.load('tex/2k_earth_daymap.jpg');
    materialEarth.map = earthTexture;

    //Moon mesh
    var geometryMoon = geometryEarth;

    var materialMoon = new THREE.MeshLambertMaterial();
    materialMoon.combine = 0;
    materialMoon.needsUpdate = true;
    materialMoon.wireframe = false; 

    const moonTexture = texloader.load('tex/2k_moon.jpg');
    materialMoon.map = moonTexture;

    //Sun Mesh
    var geometrySun = geometryEarth;

    var materialSun = new THREE.MeshBasicMaterial();
    materialSun.combine = 0;
    materialSun.needsUpdate = true;
    materialSun.wireframe = false; 

    const sunTexture = texloader.load('tex/2k_sun.jpg');
    materialSun.map = sunTexture;

    //Mars Mesh
    var geometryMars = geometryEarth;

    var materialMars = new THREE.MeshLambertMaterial();
    materialMars.combine = 0;
    materialMars.needsUpdate = true;
    materialMars.wireframe = false; 

    const marsTexture = texloader.load('tex/2k_mars.jpg');
    materialMars.map = marsTexture;

    // Task 2: uncommenting the following two lines requires you to run this example with a (local) webserver
    // see https://threejs.org/docs/#manual/en/introduction/How-to-run-things-locally
    //
    

    // Task 8: material using custom Vertex Shader and Fragment Shader
    
	var uniforms = THREE.UniformsUtils.merge( [
	    { 
	    	colorTexture : { value : new THREE.Texture() },
	    	specularMap : { value : new THREE.Texture() }
    	},
	    THREE.UniformsLib[ "lights" ]
	] );

	const shaderMaterial = new THREE.ShaderMaterial({
		uniforms : uniforms,
		vertexShader : document.getElementById('vertexShader').textContent.trim(),
		fragmentShader : document.getElementById('fragmentShader').textContent.trim(),
        lights : true,
    });
    
    shaderMaterial.uniforms.colorTexture.value = earthTexture;
    
	const specularMap = texloader.load('tex/2k_earth_specular_map.jpg');
	shaderMaterial.uniforms.specularMap.value = specularMap;
	
    earthMesh = new THREE.Mesh(geometryEarth, shaderMaterial);
    moonMesh = new THREE.Mesh(geometryMoon, materialMoon);
    sunMesh = new THREE.Mesh(geometrySun, materialSun);
    marsMesh = new THREE.Mesh(geometryMars, materialMars);

    createSceneGraph();

    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(0x000000);
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setSize(window.innerWidth, window.innerHeight);

    container.appendChild(renderer.domElement);

    document.addEventListener('mousemove', onDocumentMouseMove, false);
    window.addEventListener('resize', onWindowResize, false);

    var checkBoxAnim = document.getElementById('animation');
    animation = checkBoxAnim.checked;
    checkBoxAnim.addEventListener('change', (event) => {
    	animation = event.target.checked;
    });

	var checkBoxWireframe = document.getElementById('wireframe');
    earthMesh.material.wireframe = checkBoxWireframe.checked;
    sunMesh.material.wireframe = checkBoxWireframe.checked;
    moonMesh.material.wireframe = checkBoxWireframe.checked;
    marsMesh.material.wireframe = checkBoxWireframe.checked;
    checkBoxWireframe.addEventListener('change', (event) => {
        earthMesh.material.wireframe = event.target.checked;
        sunMesh.material.wireframe = event.target.checked;
        moonMesh.material.wireframe = event.target.checked;
        marsMesh.material.wireframe = event.target.checked;
    });

   
}

function render() {
    // Set up the camera
    camera.position.x = mouseX * 10;
    camera.position.y = -mouseY * 10;
    camera.lookAt(scene.position);

    // Perform animations
    
    earthTilt.rotation.z = THREE.MathUtils.degToRad( 23.44 );
    earthTransl.position.x = 6;
    earthScale.scale.set(0.6,0.6, 0.6);

    moonScale.scale.set(0.2, 0.2, 0.2);
    moonTransl.position.x = 8;

    sunScale.scale.set(1.3, 1.3, 1.3);

    marsTransl.position.x = 7;
    if (animation) {
        marsOrbit.rotation.y += THREE.MathUtils.degToRad((360/60)/90);
        marsSpin.rotation.y += THREE.MathUtils.degToRad((360/60)/4);
        
        moonOrbit.rotation.y += THREE.MathUtils.degToRad((-365/60)+((360/60)/27.3));
        earthOrbit.rotation.y += THREE.MathUtils.degToRad((360/60)/365);
        earthSpin.rotation.y += THREE.MathUtils.degToRad(365/60);

        sunSpin.rotation.y += THREE.MathUtils.degToRad((360/60)/25);
    }
   
    // Render the scene
    renderer.render(scene, camera);
}

function animate() {
    requestAnimationFrame(animate); // Request to be called again for next frame
    render();
}

init(); // Set up the scene
animate(); // Enter an infinite loop
