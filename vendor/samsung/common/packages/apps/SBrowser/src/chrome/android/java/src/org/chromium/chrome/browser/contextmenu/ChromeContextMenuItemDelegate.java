// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.contextmenu;

import org.chromium.chrome.browser.TabBase;
import org.chromium.content.browser.ContentView;

/**
 * A delegate responsible for taking actions based on context menu selections.
 */
public interface ChromeContextMenuItemDelegate {
    /**
     * @return Whether or not this context menu is being shown for an incognito {@link ContentView}.
     */
    boolean isIncognito();

    /**
     * @return Whether or not the current application can show incognito tabs.
     */
    boolean isIncognitoSupported();

    /**
     * @return Whether or not the context menu should give the user the chance to show the original
     *         image.
     */
    boolean canLoadOriginalImage();

    /**
     * Called when the context menu is trying to start a download.
     * @param isLink Whether or not the download is a link (as opposed to an image/video).
     * @return       Whether or not a download should actually be started.
     */
    boolean startDownload(boolean isLink);

    /**
     * Called when the {@code url} should be opened in a new tab with the same incognito state as
     * the current {@link TabBase}.
     * @param url The URL to open.
     */
    void onOpenInNewTab(String url);

    /**
     * Called when the {@code url} should be opened in a new incognito tab.
     * @param url The URL to open.
     */
    void onOpenInNewIncognitoTab(String url);

    /**
     * Called when the {@code url} is of an image and should be opened in the same tab.
     * @param url The image URL to open.
     */
    void onOpenImageUrl(String url);

    /**
     * Called when the {@code url} is of an image and should be opened in a new tab.
     * @param url The image URL to open.
     */
    void onOpenImageInNewTab(String url);

    /**
     * Called when the {@code text} should be saved to the clipboard.
     * @param text  The text to save to the clipboard.
     * @param isUrl Whether or not the text is a URL.
     */
    void onSaveToClipboard(String text, boolean isUrl);

    /**
     * Called when the {@code url} is of an image and a link to the image should be saved to the
     * clipboard.
     * @param url The image URL.
     */
    void onSaveImageToClipboard(String url);

    /**
     * Called when a search by image should be performed in a new tab.
     */
    void onSearchByImageInNewTab();

    /**
     * Added api to use customize download (SBrowserContextMenuDownloader).
     * @param isUrl Whether the selected item is a image/video or link
     * @param url The URL to download
     */
    void startContextMenuDownload(boolean isUrl, String url);

    /**
     * Added api to add open option in contextmenu .
     * @param linkUrl The URL to open
     */
    void onOpenInSameTab(String linkUrl);
}