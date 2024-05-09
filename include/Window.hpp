#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "Surface.hpp"
#include "bool.hpp"
#pragma once
namespace SDL_OOP{
    class Window {
    private:
        SDL_Window * window;
    public:
        Window(const char *title,int x, int y, int w,int h, Uint32 flags){
            this->window = SDL_CreateWindow(title, x, y, w, h, flags);
        }
        Window(const void *data){
            this->window = SDL_CreateWindowFrom(data);
        }
        Window (SDL_Window * window){
            this->window = window;
        }
        int FlashOperation(SDL_FlashOperation operation){
            return SDL_FlashWindow(this->window, operation);
        }
        SDL_Window* Getraw() {
            return this->window;
        }
        int GetBordersSize (int *top, int *left, int *bottom, int *right){
            return SDL_GetWindowBordersSize(this->window, top,left,bottom,right);
        }
        float GetBrightness(){
            return SDL_GetWindowBrightness(this->window);
        }
        int GetDisplayIndex(){
            return SDL_GetWindowDisplayIndex(this->window);
        }
        int GetDisplayMode(SDL_DisplayMode *mode){
            return SDL_GetWindowDisplayMode(this->window,mode);
        }
        void* GetData(const char *name){
            return SDL_GetWindowData(this->window, name);
        };
        Uint32 GetFlags(){
            return SDL_GetWindowFlags(this->window);
        };
        bool GetGrab(){
            return CastBool::toBool(SDL_GetWindowGrab(this->window));
        }
        bool GetKeyboardGrab(){
            return CastBool::toBool(SDL_GetWindowKeyboardGrab(this->window));
        }
        bool GetMouseGrab(){
            return CastBool::toBool(SDL_GetWindowMouseGrab(this->window));
        }
        void GetPosition(int *x, int *y){
            SDL_GetWindowPosition(this->window, x, y);
        }
        void GetSize(int *w,int *h){
            SDL_GetWindowSize(this->window, w, h);
        }
        const char* GetTitle(){
            return SDL_GetWindowTitle(this->window);
        }
        void GetMaximumSize(int* w, int* h) {
            SDL_GetWindowMaximumSize(this->window, w, h);
        }
        void GetMinimumSize(int* w, int* h) {
            SDL_GetWindowMinimumSize(this->window, w, h);
        }
        const SDL_Rect* GetMouseRect() {
            return SDL_GetWindowMouseRect(this->window);
        }

        static Window GetWindowfromID(Uint32 id){
            return Window(SDL_GetWindowFromID(id));
        }
        int GetGammaRamp(Uint16* red, Uint16* green, Uint16* blue) {
            return SDL_GetWindowGammaRamp(this->window, red, green, blue);
        }
        void* GetICCProfile(size_t * data) {
            return SDL_GetWindowICCProfile(this->window, data);
        }
        Uint32 GetID() {
            return SDL_GetWindowID(this->window);
        }
        int GetOpacity(float* out_opacity) {
            return SDL_GetWindowOpacity(this->window, out_opacity);
        }
        Uint32 GetPixelFormat() {
            return SDL_GetWindowPixelFormat(this->window);
        }
        void GetSizeInPixels(int* w, int* h) {
            SDL_GetWindowSizeInPixels(this->window, w, h);
        }
        Surface GetSurface() {
            return Surface(SDL_GetWindowSurface(this->window));
        }
        bool GetWMInfo(SDL_SysWMinfo* info) {
            return CastBool::toBool(SDL_GetWindowWMInfo(this->window, info));
        }
        void Hide(){
            SDL_HideWindow(this->window);
        }
        void Maximize(){
            SDL_MaximizeWindow(this->window);
        }
        void Minimize(){
            SDL_MinimizeWindow(this->window);
        }
        void Raise(){
            SDL_RaiseWindow(this->window);
        }
        void Restore(){
            SDL_RestoreWindow(this->window);
        }
        void* SetData(const char *name,void *userdata){
            return SDL_SetWindowData(this->window, name, userdata);
        }
        int SetFullscreen(Uint32 flags){
            return SDL_SetWindowFullscreen(this->window, flags);
        }
        void SetGrab(bool grabbed){
            SDL_SetWindowGrab(this->window, CastBool::toSDLBool(grabbed));
        }
        void SetKeyboardGrab(bool grabbed){
            SDL_SetWindowKeyboardGrab(this->window,CastBool::toSDLBool(grabbed));
        }
        void SetMouseGrab(bool grabbed){
            SDL_SetWindowMouseGrab(this->window, CastBool::toSDLBool(grabbed));
        }
        void SetIcon(Surface icon){
            SDL_SetWindowIcon(this->window, icon.GetRaw());
        }
        void SetPosition(int x, int y){
            SDL_SetWindowPosition(this->window, x, y);
        }
        void SetSize(int w,int h){
            SDL_SetWindowSize(this->window, w, h);
        }
        void SetBordered(bool bordered){
            SDL_SetWindowBordered(this->window, CastBool::toSDLBool(bordered));
        }
        void SetResizable(bool resizable){
            SDL_SetWindowResizable(this->window, CastBool::toSDLBool(resizable));
        }
        void SetTitle(const char *title){
            SDL_SetWindowTitle(this->window,title);
        }
        void SetAlwaysOnTop(bool on_top) {
            SDL_SetWindowAlwaysOnTop(this->window, CastBool::toSDLBool(on_top));
        }
        int SetBrightness(float brightness) {
            return SDL_SetWindowBrightness(this->window, brightness);
        }
        int SetDisplayMode(const SDL_DisplayMode* mode) {
            return SDL_SetWindowDisplayMode(this->window, mode);
        }
        int SetGammaRamp(const Uint16* red, const Uint16* green, const Uint16* blue) {
            return SDL_SetWindowGammaRamp(this->window, red, green, blue);
        }
        int SetHitTest(SDL_HitTest callback, void* callback_data) {
            return SDL_SetWindowHitTest(this->window, callback, callback_data);
        }
        int SetInputFocus() {
            return SDL_SetWindowInputFocus(this->window);
        }
        void SetMaximumSize(int max_w, int max_h) {
            SDL_SetWindowMaximumSize(this->window,max_w, max_h);
        }
        void SetMinimumSize(int min_w, int min_h) {
            SDL_SetWindowMinimumSize(this->window, min_w, min_h);
        }
        int SetModalFor(Window parent_window) {
            return SDL_SetWindowModalFor(this->window,parent_window.Getraw());
        }
        int SetMouseRect(const SDL_Rect* rect) {
            return SDL_SetWindowMouseRect(this->window, rect);
        }
        int SetOpacity(float opacity){
            return SDL_SetWindowOpacity(this->window, opacity);
        }
        int SetShape(Surface* shape, SDL_WindowShapeMode* shape_mode) {
            return SDL_SetWindowShape(this->window, shape->GetRaw(), shape_mode);
        }
       
        void Show(){
            SDL_ShowWindow(this->window);
        }
        ~Window(){
            SDL_DestroyWindow(this->window);
        }

    };
} ;
