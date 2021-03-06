/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2012 The MITRE Corporation                                      *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <openbr/plugins/openbr_internal.h>

namespace br
{

/*!
 * \ingroup transforms
 * \brief Add landmarks to the template in a grid layout
 * \author Josh Klontz \cite jklontz
 */
class GridTransform : public UntrainableTransform
{
    Q_OBJECT
    Q_PROPERTY(int rows READ get_rows WRITE set_rows RESET reset_rows STORED false)
    Q_PROPERTY(int columns READ get_columns WRITE set_columns RESET reset_columns STORED false)
    BR_PROPERTY(int, rows, 1)
    BR_PROPERTY(int, columns, 1)

    void project(const Template &src, Template &dst) const
    {
        QList<QPointF> landmarks;
        const float row_step = 1.f * src.m().rows / rows;
        const float column_step = 1.f * src.m().cols / columns;
        for (float y=row_step/2; y<src.m().rows; y+=row_step)
            for (float x=column_step/2; x<src.m().cols; x+=column_step)
                landmarks.append(QPointF(x,y));
        dst = src;
        dst.file.setPoints(landmarks);
    }
};

BR_REGISTER(Transform, GridTransform)

} // namespace br

#include "metadata/grid.moc"
