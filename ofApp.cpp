#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh_list.clear();
	this->frame_list.clear();

	for (int x = -160; x <= 160; x += 320) {

		for (int i = 0; i < 20; i++) {

			ofMesh mesh, frame;
			frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
			auto base = glm::vec3(x, 0, 0);
			auto param = glm::vec3();
			switch ((int)ofRandom(3)) {
			case 0:
				param = glm::vec3(5, 0, 0);
				break;
			case 1:
				param = glm::vec3(0, 5, 0);
				break;
			case 2:
				param = glm::vec3(0, 0, 5);
				break;
			}

			auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

			for (int k = 0; k < 50; k++) {

				auto location = glm::vec3(
					ofMap(ofNoise(noise_seed.x, (k + ofGetFrameNum()) * 0.01), 0, 1, -150, 150),
					ofMap(ofNoise(noise_seed.y, (k + ofGetFrameNum()) * 0.01), 0, 1, -150, 150),
					ofMap(ofNoise(noise_seed.z, (k + ofGetFrameNum()) * 0.01), 0, 1, -150, 150));

				location = glm::normalize(location) * 150;

				mesh.addVertex(base + location + param);
				mesh.addVertex(base + location - param);

				frame.addVertex(base + location + param);
				frame.addVertex(base + location - param);

				if (k > 0) {

					mesh.addIndex(k * 2); mesh.addIndex(k * 2 - 1); mesh.addIndex(k * 2 - 2);
					mesh.addIndex(k * 2); mesh.addIndex(k * 2 + 1); mesh.addIndex(k * 2 - 1);

					frame.addIndex(k * 2); frame.addIndex(k * 2 - 2);
					frame.addIndex(k * 2 + 1); frame.addIndex(k * 2 - 1);
				}
			}

			frame.addIndex(0); frame.addIndex(1);
			frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);

			this->mesh_list.push_back(mesh);
			this->frame_list.push_back(frame);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	ofDrawSphere(glm::vec3(-160, 0, 0), 135);

	for (int i = 0; i < this->mesh_list.size(); i++) {

		ofSetColor(39);
		this->mesh_list[i].draw();

		ofSetColor(239);
		this->frame_list[i].drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}