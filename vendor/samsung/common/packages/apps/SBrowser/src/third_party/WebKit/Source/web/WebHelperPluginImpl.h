/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebHelperPluginImpl_h
#define WebHelperPluginImpl_h

#include "WebHelperPlugin.h"
#include "wtf/OwnPtr.h"

namespace WebCore {
class Page;
}

namespace blink {

class HelperPluginChromeClient;
class HelperPluginFrameClient;
class WebDocument;
class WebFrameImpl;
class WebViewImpl;
class WebWidgetClient;

// Hosts a simple page that instantiates a plugin using an <object> tag.
// The widget is offscreen, and the plugin will not receive painting, resize, etc. events.
class WebHelperPluginImpl FINAL : public WebHelperPlugin {
    WTF_MAKE_NONCOPYABLE(WebHelperPluginImpl);
    WTF_MAKE_FAST_ALLOCATED;

public:
    // WebHelperPlugin methods:
    virtual void initializeFrame(WebFrameClient*) OVERRIDE;
    virtual WebPlugin* getPlugin() OVERRIDE;
    virtual void closeAndDeleteSoon() OVERRIDE;

    bool initialize(const String& pluginType, const WebDocument& hostDocument, WebViewImpl*);
    // Called asynchronously and only by WebViewImpl.
    void closeAndDelete();

private:
    explicit WebHelperPluginImpl(WebWidgetClient*);
    bool initializePage(const WebString& pluginType, const WebDocument& hostDocument);
    void destroyPage();

    // This object needs to be destroyed by calling closeAndDelete().
    virtual ~WebHelperPluginImpl();

    // WebWidget methods:
    virtual void layout() OVERRIDE;
    virtual void setFocus(bool) OVERRIDE;
    virtual void close() OVERRIDE;
    virtual bool isHelperPlugin() const OVERRIDE { return true; }

    WebWidgetClient* m_widgetClient;
    WebViewImpl* m_webView;
    WebFrameImpl* m_mainFrame;
    OwnPtr<WebCore::Page> m_page;
    OwnPtr<HelperPluginChromeClient> m_chromeClient;
    OwnPtr<HelperPluginFrameClient> m_frameClient;

    friend class WebHelperPlugin;
    friend class HelperPluginChromeClient;
};

DEFINE_TYPE_CASTS(WebHelperPluginImpl, WebWidget, widget, widget->isHelperPlugin(), widget.isHelperPlugin());

} // namespace blink

#endif // WebHelperPluginImpl_h
