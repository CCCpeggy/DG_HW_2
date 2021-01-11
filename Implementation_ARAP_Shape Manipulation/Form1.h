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
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "ArapInteractor_2.h"
#include "vavImage.h"
#include "TriangulationCgal.h"

#pragma region Application variables

vavImage	  *ImageEdge=NULL;	   //find contour
TriangulationCgal *Triangulate=NULL;	   //Delaunay triangulation	

TriMesh2D	  *test_1=NULL;		   	
ShapeView	  *ShapeView_Object=NULL;
ArapInteractor    *Arap=NULL;

int		  flag=-1;
int		  mouseX,mouseY;

struct Mode_Display {
	bool openImg;
	bool triangulation;
};

Mode_Display Current_Display;
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
			ImageEdge= new vavImage;
			

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

	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

	private: System::ComponentModel::IContainer^  components;

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
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Location = System::Drawing::Point(136, 13);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(734, 682);
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
			this->button2->Size = System::Drawing::Size(118, 107);
			this->button2->TabIndex = 11;
			this->button2->Text = L"Open Img";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click_1);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 135);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(118, 114);
			this->button3->TabIndex = 12;
			this->button3->Text = L"triangulation";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(887, 707);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Name = L"Form1";
			this->Text = L"As rigid as possible shape manipulation";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
	private: System::Void dotNetBarManager1_ItemClick(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 hkoglPanelControl1->Invalidate();
	 }
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
		 if(e->Button==System::Windows::Forms::MouseButtons::Left)//move the control point
		 {
			 if(flag!=-1)
			 {
				 //std::cout<<"position X:"<<e->X<<" Y:"<<e->Y<<std::endl;
				 //==========================
// 				 clock_t start, finish;
// 				 start = clock();
				 //==========================
				 Arap->OnMotion(e->X-50,e->Y-50,flag,1,1);//0.008s

				 //==============================
// 				 finish = clock();
// 				 cout <<"Time Consume :" <<(double)(finish - start) / CLOCKS_PER_SEC<<endl;
				 //==============================
				 hkoglPanelControl1->Invalidate();
			 }		
		 }

	 }
private: System::Void hkoglPanelControl1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 if(e->Button==System::Windows::Forms::MouseButtons::Left && mouseX==e->X && mouseY==e->Y)//add the control point
		 {	
			 Arap->OnMouse(0,1,e->X-50,e->Y-50);
		 }
		 if(e->Button==System::Windows::Forms::MouseButtons::Right)				  //delete the control point
		 {
			 Arap->OnMouse(2,1,e->X-50,e->Y-50);
		 }
		 hkoglPanelControl1->Invalidate();
	 }
private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 if(e->Button==System::Windows::Forms::MouseButtons::Left)
		 {
			mouseX=e->X;
			mouseY=e->Y;
			flag=Arap->getVertex(e->X-50,e->Y-50);						 //get control point ID
		 }
	 }
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {//open image 
		 Current_Display.openImg=1;
		 ImageEdge->ReadImage("gingerbread_man.bmp");
		 *ImageEdge = (ImageEdge->CannyEdge());
	 
		 std::cout<<"Load img :"<<ImageEdge->GetHeight()<<"*"<<ImageEdge->GetWidth()<<std::endl;
	 
		 hkoglPanelControl1->Invalidate();
	 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {//CGAL Delaunay Triangulation
		 if(Current_Display.openImg)
		 {
			 Current_Display.triangulation=1;
			 Current_Display.openImg=0;
			 Triangulate=new TriangulationCgal;
			 Triangles Tris;
			 Vector2s meshPointset;
			 Vector2s ContourPoint=ImageEdge->GetContour();

			 for(int i=0;i<ContourPoint.size();i+=15)
			 {
				  Triangulate->AddPoint(ContourPoint[i][0],ContourPoint[i][1]);
			 }

			 Triangulate->DelaunayMesher2();
			 meshPointset=Triangulate->MeshPointSet();

			 for(int i=0 ;i < meshPointset.size() ; i++ )
			 {
				 test_1->vertices.push_back(Point2D(meshPointset[i][0],meshPointset[i][1]));
			 }

 			 Tris=Triangulate->GetTriangles();
 			 std::cout<<"Tris.size() :"<<Tris.size()<<std::endl;
			 Tri v;
			 for(int i=0;i<Tris.size();i++)
			 {
				 if(!ImageEdge->IsinsidePoint(Tris[Tris.size()-1-i].m_Points[0][0],Tris[Tris.size()-1-i].m_Points[0][1],
					 Tris[Tris.size()-1-i].m_Points[1][0],Tris[Tris.size()-1-i].m_Points[1][1],
					 Tris[Tris.size()-1-i].m_Points[2][0],Tris[Tris.size()-1-i].m_Points[2][1]))
 					 continue;
				 for(int j=0;j<3;j++)
				 {
					 v[j]=Triangulate->getVertexID(Tris[Tris.size()-1-i].m_Points[j][0],Tris[Tris.size()-1-i].m_Points[j][1]);
				 }
				test_1->tris.push_back(v);
			 }
 			 Arap= new ArapInteractor(ShapeView_Object,*test_1);

		 }
		 hkoglPanelControl1->Invalidate();
	 }
};
}

