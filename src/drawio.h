/******************************************************************************
 *
 * Copyright (C) 1997-2015 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef DRAWIO_H
#define DRAWIO_H

#include <qdict.h>
#include <qlist.h>

/** Singleton that manages drawio relation actions */
class DrawioManager
{
  public:
    /** Plant UML output image formats */
    enum OutputFormat { PUML_BITMAP, PUML_EPS, PUML_SVG };

    static DrawioManager *instance();

    /** Run plant UML tool for all images */
    void run();

    /** Convert a drawio file to an image.
     *  @param[in] baseName the name of the generated file (as returned by writePlantUMLSource())
     *  @param[in] outDir   the directory to write the resulting image into.
     *  @param[in] format   the image format to generate.
     */
    void generateDrawioOutput(const char *baseName,const char *outDir,OutputFormat format);

  private:
    DrawioManager();
    ~DrawioManager();
    void insert(const QCString &key, 
                const QCString &value,
                const QCString &outDir,
                OutputFormat format,
                const QCString &puContent);
    static DrawioManager        *m_theInstance;
    QDict< QList<QCString> >    m_pngPlantumlFiles;
    QDict< QList<QCString> >    m_svgPlantumlFiles;
    QDict< QList<QCString> >    m_epsPlantumlFiles;
    QDict< DrawioManager >      m_pngPlantumlContent;     // use circular queue for using multi-processor (multi threading)
    QDict< DrawioManager >      m_svgPlantumlContent;
    QDict< DrawioManager >      m_epsPlantumlContent;
    QCString                    m_cachedPlantumlAllContent;         // read from CACHE_FILENAME file
    QCString                    m_currentPlantumlAllContent;        // processing plantuml then write it into CACHE_FILENAME to reuse the next time as cache information
};

#endif

