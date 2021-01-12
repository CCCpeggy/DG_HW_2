//==========================================================================
//  This is the implementation of As-Rigid-As-Possible Shape Manipulation
//==========================================================================
#pragma once
#define BOOST_ALL_DYN_LINK
//#pragma comment(linker, "/SUBSYSTEM:CONSOLE /ENTRY:WinMainCRTStartup")
//#define _USE_MATH_DEFINES
//#define NOMINMAX
#include <windows.h>
#include <vector>
#include <cmath>
#include <time.h>

#include <iostream>
#include <fstream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "ArapInteractor_2.h"
#include "vavImage.h"
#include "TriangulationCgal.h"
#include "Common.h"

#pragma region Application variables

vavImage* ImageEdge = NULL;	   //find contour
TriangulationCgal* Triangulate = NULL;	   //Delaunay triangulation	

TriMesh2D* test_1 = NULL, *savedTest=NULL;
ShapeView* ShapeView_Object = NULL;
ArapInteractor* Arap = NULL;

int		  *savedFlags = NULL, savedFlagSize = 0;
int		  flag = -1;
int		  mouseX, mouseY;
bool isweightopen = false;
extern bool step1_only;
extern bool show_fitted;
extern bool depth;
extern bool animation;
extern bool peeking;

struct Mode_Display {
	bool openImg;
	bool triangulation;
};

Mode_Display Current_Display;

struct MoveAction {
	int flag;
	int X;
	int Y;
};
std::vector<MoveAction> actions;
#pragma endregion

namespace As_rigid_as_test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			test_1 = new TriMesh2D;
			savedTest = new TriMesh2D;
			ImageEdge = new vavImage;

			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: HKOGLPanel::HKOGLPanelControl^ hkoglPanelControl1;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::CheckBox^ depth;
	private: System::Windows::Forms::CheckBox^ weight;
	private: System::Windows::Forms::CheckBox^ Scale;

	private: System::Windows::Forms::CheckBox^ fit;
	private: System::Windows::Forms::Button^ start_anime;
	private: System::Windows::Forms::Button^ record_anime;
	private: System::Windows::Forms::Button^ stop_anime;

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^ hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^ hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->depth = (gcnew System::Windows::Forms::CheckBox());
			this->weight = (gcnew System::Windows::Forms::CheckBox());
			this->Scale = (gcnew System::Windows::Forms::CheckBox());
			this->fit = (gcnew System::Windows::Forms::CheckBox());
			this->start_anime = (gcnew System::Windows::Forms::Button());
			this->record_anime = (gcnew System::Windows::Forms::Button());
			this->stop_anime = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Location = System::Drawing::Point(172, 13);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(800, 682);
			this->hkoglPanelControl1->TabIndex = 9;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &Form1::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseClick);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseMove);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(126, 107);
			this->button2->TabIndex = 11;
			this->button2->Text = L"Open Img";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click_1);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 135);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(126, 114);
			this->button3->TabIndex = 12;
			this->button3->Text = L"triangulation";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// depth
			// 
			this->depth->AutoSize = true;
			this->depth->Location = System::Drawing::Point(13, 413);
			this->depth->Name = L"depth";
			this->depth->Size = System::Drawing::Size(50, 16);
			this->depth->TabIndex = 15;
			this->depth->Text = L"depth";
			this->depth->UseVisualStyleBackColor = true;
			// 
			// weight
			// 
			this->weight->AutoSize = true;
			this->weight->Location = System::Drawing::Point(13, 378);
			this->weight->Name = L"weight";
			this->weight->Size = System::Drawing::Size(55, 16);
			this->weight->TabIndex = 16;
			this->weight->Text = L"weight";
			this->weight->UseVisualStyleBackColor = true;
			this->weight->CheckedChanged += gcnew System::EventHandler(this, &Form1::weight_CheckedChanged);
			// 
			// Scale
			// 
			this->Scale->AutoSize = true;
			this->Scale->Checked = true;
			this->Scale->CheckState = System::Windows::Forms::CheckState::Checked;
			this->Scale->Location = System::Drawing::Point(82, 346);
			this->Scale->Name = L"Scale";
			this->Scale->Size = System::Drawing::Size(46, 16);
			this->Scale->TabIndex = 19;
			this->Scale->Text = L"scale";
			this->Scale->UseVisualStyleBackColor = true;
			this->Scale->CheckedChanged += gcnew System::EventHandler(this, &Form1::Scale_CheckedChanged);
			// 
			// fit
			// 
			this->fit->AutoSize = true;
			this->fit->Location = System::Drawing::Point(13, 346);
			this->fit->Name = L"fit";
			this->fit->Size = System::Drawing::Size(61, 16);
			this->fit->TabIndex = 14;
			this->fit->Text = L"show fit";
			this->fit->UseVisualStyleBackColor = true;
			this->fit->CheckedChanged += gcnew System::EventHandler(this, &Form1::fit_CheckedChanged);
			// 
			// start_anime
			// 
			this->start_anime->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->start_anime->Location = System::Drawing::Point(12, 271);
			this->start_anime->Name = L"start_anime";
			this->start_anime->Size = System::Drawing::Size(38, 35);
			this->start_anime->TabIndex = 20;
			this->start_anime->Text = L"▶";
			this->start_anime->UseVisualStyleBackColor = true;
			this->start_anime->Click += gcnew System::EventHandler(this, &Form1::start_anime_Click);
			// 
			// record_anime
			// 
			this->record_anime->Font = (gcnew System::Drawing::Font(L"新細明體", 10));
			this->record_anime->Location = System::Drawing::Point(56, 271);
			this->record_anime->Name = L"record_anime";
			this->record_anime->Size = System::Drawing::Size(38, 35);
			this->record_anime->TabIndex = 21;
			this->record_anime->Text = L"⚫";
			this->record_anime->UseVisualStyleBackColor = true;
			this->record_anime->Click += gcnew System::EventHandler(this, &Form1::record_anime_Click);
			// 
			// stop_anime
			// 
			this->stop_anime->Font = (gcnew System::Drawing::Font(L"新細明體", 8));
			this->stop_anime->Location = System::Drawing::Point(100, 271);
			this->stop_anime->Name = L"stop_anime";
			this->stop_anime->Size = System::Drawing::Size(38, 35);
			this->stop_anime->TabIndex = 22;
			this->stop_anime->Text = L"█";
			this->stop_anime->UseVisualStyleBackColor = true;
			this->stop_anime->Click += gcnew System::EventHandler(this, &Form1::stop_anime_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1011, 707);
			this->Controls->Add(this->stop_anime);
			this->Controls->Add(this->record_anime);
			this->Controls->Add(this->start_anime);
			this->Controls->Add(this->Scale);
			this->Controls->Add(this->weight);
			this->Controls->Add(this->depth);
			this->Controls->Add(this->fit);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Name = L"Form1";
			this->Text = L"As rigid as possible shape manipulation";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Render_Init(hkoglPanelControl1->Size.Width, hkoglPanelControl1->Size.Height);
		if(Current_Display.openImg)
		{
			ImageEdge->drawImage();
		}
		if(Current_Display.triangulation)
		{
			Arap->OnDraw(); 
		}
	}
	private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e) {
		OpenGLinitial();
		PanelResize(hkoglPanelControl1->Size.Width , hkoglPanelControl1->Size.Height);
	}
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left)//move the control point
		{
			if (flag != -1)
			{
				//std::cout<<"position X:"<<e->X<<" Y:"<<e->Y<<std::endl;
				//==========================
// 				 clock_t start, finish;
// 				 start = clock();
				 //==========================
				while (!Arap->OnMotion(e->X - 50, e->Y - 50, flag, 1, 1)) {//0.008s
					hkoglPanelControl1->Refresh();
				}
				hkoglPanelControl1->Invalidate();
				MoveAction newAction = { flag, e->X - 50, e->Y - 50 };
				actions.push_back(newAction);

				//==============================
// 				 finish = clock();
// 				 cout <<"Time Consume :" <<(double)(finish - start) / CLOCKS_PER_SEC<<endl;
				 //==============================
			}
			else if(isweightopen){
				Arap->selectTriangle(e->X - 50, e->Y - 50, 1);
			}
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			if ((flag == -1)&& (isweightopen == true)) {
				Arap->selectTriangle(e->X - 50, e->Y - 50, 2);
			}
		}
	}
	private: System::Void hkoglPanelControl1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left && mouseX == e->X && mouseY == e->Y)//add the control point
		{
			Arap->OnMouse(0, 1, e->X - 50, e->Y - 50);
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Right)				  //delete the control point
		{
			Arap->OnMouse(2, 1, e->X - 50, e->Y - 50);
		}
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			mouseX = e->X;
			mouseY = e->Y;
			flag = Arap->getVertex(e->X - 50, e->Y - 50);						 //get control point ID
		}
	}
private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {//open image 
		Current_Display.openImg = 1;
		ImageEdge->ReadImage("full_guys_mask.png"); 
		glEnable(GL_TEXTURE_2D);// 启用2D纹理
		*ImageEdge = (ImageEdge->CannyEdge());

		GLuint textureID;
		loadTextures(textureID, "full_guys.png");
		glBindTexture(GL_TEXTURE_2D, textureID);

		std::cout << "Load img :" << ImageEdge->GetHeight() << "*" << ImageEdge->GetWidth() << std::endl;

		hkoglPanelControl1->Invalidate();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {//CGAL Delaunay Triangulation
		if (Current_Display.openImg)
		{
			Current_Display.triangulation = 1;
			Current_Display.openImg = 0;
			Triangulate = new TriangulationCgal;
			Triangles Tris;
			Vector2s meshPointset;
			Vector2s ContourPoint = ImageEdge->GetContour();

			for (int i = 0; i < ContourPoint.size(); i += 15)
			{
				Triangulate->AddPoint(ContourPoint[i][0], ContourPoint[i][1]);
			}

			Triangulate->DelaunayMesher2();
			meshPointset = Triangulate->MeshPointSet();

			for (int i = 0; i < meshPointset.size(); i++)
			{
				test_1->vertices.push_back(Point2D(meshPointset[i][0], meshPointset[i][1]));
				test_1->uvs.push_back(Point2D(meshPointset[i][0] / ImageEdge->GetHeight(), 1 - meshPointset[i][1] / ImageEdge->GetWidth()));
			}

			Tris = Triangulate->GetTriangles();
			std::cout << "Tris.size() :" << Tris.size() << std::endl;
			Tri v;
			for (int i = 0; i < Tris.size(); i++)
			{
				if (!ImageEdge->IsinsidePoint(Tris[Tris.size() - 1 - i].m_Points[0][0], Tris[Tris.size() - 1 - i].m_Points[0][1],
					Tris[Tris.size() - 1 - i].m_Points[1][0], Tris[Tris.size() - 1 - i].m_Points[1][1],
					Tris[Tris.size() - 1 - i].m_Points[2][0], Tris[Tris.size() - 1 - i].m_Points[2][1]))
					continue;
				for (int j = 0; j < 3; j++)
				{
					v[j] = Triangulate->getVertexID(Tris[Tris.size() - 1 - i].m_Points[j][0], Tris[Tris.size() - 1 - i].m_Points[j][1]);
				}
				test_1->tris.push_back(v);
			}
			Arap = new ArapInteractor(ShapeView_Object, *test_1);

		}
		hkoglPanelControl1->Invalidate();
		savedTest->vertices.resize(test_1->vertices.size(), Point2D(0, 0));
		savedTest->tris.resize(test_1->tris.size(), Tri());
		if (savedFlagSize) {
			Arap->AddControlPoints(savedFlags, savedFlagSize);
		}
	}
	private: System::Void fit_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		show_fitted = this->fit->Checked;
	}
	private: System::Void Scale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		step1_only = !this->Scale->Checked;
	}
	private: System::Void weight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		isweightopen = true;
		Arap->OnKeyboard('w', 1, 1);
	}

private: System::Void start_anime_Click(System::Object^ sender, System::EventArgs^ e) {
	for (int i = 0; i < test_1->vertices.size(); i++)
	{
		Arap->themesh.vertices[i][0] = savedTest->vertices[i][0];
		Arap->themesh.vertices[i][1] = savedTest->vertices[i][1];
	}
	hkoglPanelControl1->Invalidate();
	animation = true;
	for (int i = 0; i < actions.size(); i++) {
		while (!Arap->OnMotion(actions[i].X, actions[i].Y, actions[i].flag, 1, 1)) {//0.008s
			hkoglPanelControl1->Refresh();
			Sleep(40);
		}
	}
	animation = false;
	hkoglPanelControl1->Invalidate();
}
private: System::Void record_anime_Click(System::Object^ sender, System::EventArgs^ e) {
	actions.clear();
	animation = true;
	for (int i = 0; i < test_1->vertices.size(); i++)
	{
		savedTest->vertices[i][0] = Arap->themesh.vertices[i][0];
		savedTest->vertices[i][1] = Arap->themesh.vertices[i][1];
	}
	this->record_anime->ForeColor = Color::Red;
}
private: System::Void stop_anime_Click(System::Object^ sender, System::EventArgs^ e) {
	start_anime->Enabled = actions.size() > 0;
	animation = false;
	this->record_anime->ForeColor = this->start_anime->DefaultForeColor;
	fstream file;
	file.open("Animation.txt", ios::out);
	file << test_1->vertices.size() << endl;
	for (int i = 0; i < test_1->vertices.size(); i++)
	{
		file << savedTest->vertices[i][0] << " " << savedTest->vertices[i][1] << endl;
	}

	int count = 0;
	for (int i = 0; i < Arap->flags.size(); i++) {
		if (Arap->flags[i]) count++;
	}
	file << count;
	for (int i = 0; i < Arap->flags.size(); i++) {
		if (Arap->flags[i]) {
			file << " " << i;
		}
	}
	file << endl;

	file << actions.size() << endl;
	for (int i = 0; i < actions.size(); i++) {
		file << actions[i].X << " " << actions[i].Y << " " << actions[i].flag << endl;
	}
	file.close();
}
private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	fstream file;
	file.open("Animation.txt", ios::in);
	if (!file.fail()) {
		MoveAction newAction;
		int count;
		if (file >> count) {
			savedTest->vertices.resize(count, Point2D(0, 0));
			savedTest->tris.resize(count, Tri());
			for (int i = 0; i < count; i++) {
				double x, y;
				file >> x >> y;
				savedTest->vertices[i][0] = x;
				savedTest->vertices[i][1] = y;
			}
		}
		if (file >> count) {
			savedFlags = new int[count];
			savedFlagSize = count;
			for (int i = 0; i < count; i++) {
				file >> savedFlags[i];
			}
		}
		if (file >> count) {
			while (count--) {
				file >> newAction.X >> newAction.Y >> newAction.flag;
				actions.push_back(newAction);
			}
		}
	}
	for (int i = 0; i < actions.size(); i++) {
		file << actions[i].X << " " << actions[i].Y << " " << actions[i].flag << endl;
	}
	file.close();
	this->start_anime->Enabled = actions.size() > 0;
}
};
}

