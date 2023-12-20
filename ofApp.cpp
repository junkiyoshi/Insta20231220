#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	ofColor color;
	this->number_of_sphere = 1500;

	while (this->sphere_list.size() < this->number_of_sphere) {

		auto tmp_location = this->make_point(280, ofRandom(0, 50), ofRandom(360), ofRandom(360));
		auto radius = this->sphere_list.size() < 100 ? ofRandom(20, 50) : ofRandom(5, 20);

		bool flag = true;
		for (int i = 0; i < this->sphere_list.size(); i++) {

			if (glm::distance(tmp_location, get<1>(this->sphere_list[i])) < get<2>(this->sphere_list[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {
			
			color.setHsb(ofRandom(255), 180, 255);
			auto size = (radius * 2) / sqrt(3);
			this->sphere_list.push_back(make_tuple(color, tmp_location, size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.777);

	for (int i = 0; i < this->sphere_list.size(); i++) {

		auto color = get<0>(this->sphere_list[i]);
		auto location = get<1>(this->sphere_list[i]);
		auto size = get<2>(this->sphere_list[i]);

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));
		ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));
		ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));

		auto noise_value = ofNoise(glm::vec4(location * 0.01, ofGetFrameNum() * 0.025));
		auto tmp_size = noise_value < 0.5 ? size * 0.2 : ofMap(noise_value, 0.5, 1, size * 0.2, size * 0.8);

		ofFill();
		ofSetColor(color);
		ofDrawSphere(tmp_size);

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}